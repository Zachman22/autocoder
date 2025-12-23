# AutoCoder Windows Installer Build Script
# Builds the project and creates NSIS installer

$ErrorActionPreference = "Stop"

Write-Host "`n=== AutoCoder Windows Installer Build ===" -ForegroundColor Cyan

# Configuration
$VCPKG_ROOT = "C:\vcpkg"
$PROJECT_DIR = $PSScriptRoot
$BUILD_DIR = Join-Path $PROJECT_DIR "build"
$RELEASE_DIR = Join-Path $BUILD_DIR "Release"

# Check for NSIS
$nsisPath = "C:\Program Files (x86)\NSIS\makensis.exe"
if (-not (Test-Path $nsisPath)) {
    Write-Host "✗ NSIS not found at $nsisPath" -ForegroundColor Red
    Write-Host "`nPlease install NSIS from: https://nsis.sourceforge.io/Download" -ForegroundColor Yellow
    Write-Host "Or via Chocolatey: choco install nsis" -ForegroundColor Yellow
    exit 1
}

# Check for vcpkg
if (-not (Test-Path $VCPKG_ROOT)) {
    Write-Host "✗ vcpkg not found at $VCPKG_ROOT" -ForegroundColor Red
    Write-Host "Please run build-windows.ps1 first to set up vcpkg and Qt6" -ForegroundColor Yellow
    exit 1
}

# Step 1: Build the project
Write-Host "`nStep 1: Building AutoCoder..." -ForegroundColor Yellow
if (Test-Path $BUILD_DIR) {
    Remove-Item -Recurse -Force $BUILD_DIR
}
New-Item -ItemType Directory -Path $BUILD_DIR | Out-Null
Set-Location $BUILD_DIR

cmake .. `
    -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT\scripts\buildsystems\vcpkg.cmake" `
    -DCMAKE_BUILD_TYPE=Release `
    -DBUILD_INSTALLER=OFF `
    -DBUILD_TESTS=OFF `
    -G "Visual Studio 17 2022" `
    -A x64

if ($LASTEXITCODE -ne 0) {
    Write-Host "✗ CMake configuration failed" -ForegroundColor Red
    exit 1
}

cmake --build . --config Release -j

if ($LASTEXITCODE -ne 0) {
    Write-Host "✗ Build failed" -ForegroundColor Red
    exit 1
}

Write-Host "✓ Build complete" -ForegroundColor Green

# Step 2: Copy Qt6 DLLs
Write-Host "`nStep 2: Copying Qt6 DLLs..." -ForegroundColor Yellow

$qtBinDir = "$VCPKG_ROOT\installed\x64-windows\bin"
$qtPluginsDir = "$VCPKG_ROOT\installed\x64-windows\plugins"

if (-not (Test-Path $qtBinDir)) {
    Write-Host "✗ Qt6 binaries not found. Run build-windows.ps1 first to install Qt6." -ForegroundColor Red
    exit 1
}

# Copy Qt6 DLLs
$qtDlls = @(
    "Qt6Core.dll",
    "Qt6Gui.dll",
    "Qt6Widgets.dll",
    "Qt6Network.dll",
    "Qt6WebSockets.dll"
)

foreach ($dll in $qtDlls) {
    $source = Join-Path $qtBinDir $dll
    if (Test-Path $source) {
        Copy-Item $source $RELEASE_DIR -Force
        Write-Host "  Copied $dll" -ForegroundColor Gray
    } else {
        Write-Host "  ✗ Warning: $dll not found" -ForegroundColor Yellow
    }
}

# Copy OpenSSL DLLs
$opensslDlls = Get-ChildItem -Path $qtBinDir -Filter "libssl*.dll"
$opensslDlls += Get-ChildItem -Path $qtBinDir -Filter "libcrypto*.dll"
foreach ($dll in $opensslDlls) {
    Copy-Item $dll.FullName $RELEASE_DIR -Force
    Write-Host "  Copied $($dll.Name)" -ForegroundColor Gray
}

# Copy CURL DLL
$curlDlls = Get-ChildItem -Path $qtBinDir -Filter "libcurl*.dll"
foreach ($dll in $curlDlls) {
    Copy-Item $dll.FullName $RELEASE_DIR -Force
    Write-Host "  Copied $($dll.Name)" -ForegroundColor Gray
}

# Copy zlib and other dependencies
$additionalDlls = @(
    "zlib1.dll",
    "libpng16.dll",
    "freetype.dll",
    "bz2.dll",
    "pcre2-16.dll",
    "harfbuzz.dll",
    "double-conversion.dll"
)

foreach ($dll in $additionalDlls) {
    $source = Join-Path $qtBinDir $dll
    if (Test-Path $source) {
        Copy-Item $source $RELEASE_DIR -Force
        Write-Host "  Copied $dll" -ForegroundColor Gray
    }
}

# Step 3: Copy Qt6 plugins
Write-Host "`nStep 3: Copying Qt6 plugins..." -ForegroundColor Yellow

# Create plugins directory structure
$pluginsTarget = Join-Path $RELEASE_DIR "plugins"
New-Item -ItemType Directory -Path "$pluginsTarget\platforms" -Force | Out-Null
New-Item -ItemType Directory -Path "$pluginsTarget\styles" -Force | Out-Null
New-Item -ItemType Directory -Path "$pluginsTarget\imageformats" -Force | Out-Null

# Copy platform plugin
$platformPlugin = Join-Path $qtPluginsDir "platforms\qwindows.dll"
if (Test-Path $platformPlugin) {
    Copy-Item $platformPlugin "$pluginsTarget\platforms\" -Force
    Write-Host "  Copied qwindows.dll" -ForegroundColor Gray
}

# Copy style plugin
$stylePlugin = Join-Path $qtPluginsDir "styles\qwindowsvistastyle.dll"
if (Test-Path $stylePlugin) {
    Copy-Item $stylePlugin "$pluginsTarget\styles\" -Force
    Write-Host "  Copied qwindowsvistastyle.dll" -ForegroundColor Gray
}

# Copy image format plugins
$imagePlugins = Get-ChildItem -Path "$qtPluginsDir\imageformats" -Filter "*.dll" -ErrorAction SilentlyContinue
foreach ($plugin in $imagePlugins) {
    Copy-Item $plugin.FullName "$pluginsTarget\imageformats\" -Force
    Write-Host "  Copied $($plugin.Name)" -ForegroundColor Gray
}

Write-Host "✓ Dependencies copied" -ForegroundColor Green

# Step 4: Build NSIS installer
Write-Host "`nStep 4: Building NSIS installer..." -ForegroundColor Yellow

Set-Location $PROJECT_DIR

& $nsisPath "installer.nsi"

if ($LASTEXITCODE -ne 0) {
    Write-Host "✗ NSIS build failed" -ForegroundColor Red
    exit 1
}

Write-Host "✓ NSIS installer created" -ForegroundColor Green

# Find the installer
$installer = Get-ChildItem -Path $PROJECT_DIR -Filter "AutoCoder-*-Setup.exe" | Select-Object -First 1

if ($installer) {
    Write-Host "`n=== Installation Complete ===" -ForegroundColor Green
    Write-Host "`nInstaller created:" -ForegroundColor Cyan
    Write-Host "  Name: $($installer.Name)" -ForegroundColor White
    Write-Host "  Size: $([math]::Round($installer.Length / 1MB, 2)) MB" -ForegroundColor White
    Write-Host "  Path: $($installer.FullName)" -ForegroundColor White
    Write-Host "`n✓ Windows installer build complete!" -ForegroundColor Green
} else {
    Write-Host "✗ Installer file not found" -ForegroundColor Red
    exit 1
}

# AutoCoder Windows Build Script
# Builds Windows installer with vcpkg dependencies

$ErrorActionPreference = "Stop"

Write-Host "`n=== AutoCoder Windows Installer Build ===" -ForegroundColor Cyan
Write-Host "This script will install dependencies and build the installer`n" -ForegroundColor Cyan

# Check if vcpkg exists
$VCPKG_ROOT = "C:\vcpkg"
if (Test-Path $VCPKG_ROOT) {
    Write-Host "✓ Found vcpkg at $VCPKG_ROOT" -ForegroundColor Green
} else {
    Write-Host "Installing vcpkg..." -ForegroundColor Yellow
    git clone https://github.com/Microsoft/vcpkg.git C:\vcpkg
    Set-Location C:\vcpkg
    .\bootstrap-vcpkg.bat
    .\vcpkg integrate install
}

# Install Qt6 and dependencies via vcpkg
Write-Host "`nInstalling Qt6 and dependencies (this may take 30-60 minutes)..." -ForegroundColor Yellow
Set-Location $VCPKG_ROOT

# Install required packages
$packages = @(
    "qt6-base:x64-windows",
    "qt6-websockets:x64-windows",
    "openssl:x64-windows",
    "curl:x64-windows"
)

foreach ($package in $packages) {
    Write-Host "Installing $package..." -ForegroundColor Cyan
    .\vcpkg install $package
    if ($LASTEXITCODE -ne 0) {
        Write-Host "✗ Failed to install $package" -ForegroundColor Red
        exit 1
    }
}

Write-Host "✓ All dependencies installed" -ForegroundColor Green

# Return to project directory
$PROJECT_DIR = Split-Path -Parent $PSScriptRoot
if (-not $PROJECT_DIR) {
    $PROJECT_DIR = $PWD
}
Set-Location $PROJECT_DIR

# Clean and create build directory
Write-Host "`nSetting up build directory..." -ForegroundColor Yellow
if (Test-Path "build") {
    Remove-Item -Recurse -Force build
}
New-Item -ItemType Directory -Path "build" | Out-Null
Set-Location build

# Configure with CMake
Write-Host "`nConfiguring with CMake..." -ForegroundColor Yellow
cmake .. `
    -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT\scripts\buildsystems\vcpkg.cmake" `
    -DCMAKE_BUILD_TYPE=Release `
    -DBUILD_INSTALLER=ON `
    -DBUILD_TESTS=OFF `
    -G "Visual Studio 17 2022" `
    -A x64

if ($LASTEXITCODE -ne 0) {
    Write-Host "✗ CMake configuration failed" -ForegroundColor Red
    exit 1
}

Write-Host "✓ Configuration complete" -ForegroundColor Green

# Build
Write-Host "`nBuilding project..." -ForegroundColor Yellow
cmake --build . --config Release -j

if ($LASTEXITCODE -ne 0) {
    Write-Host "✗ Build failed" -ForegroundColor Red
    exit 1
}

Write-Host "✓ Build complete" -ForegroundColor Green

# Create installer
Write-Host "`nGenerating Windows installer..." -ForegroundColor Yellow

# Try NSIS first (if available)
Write-Host "Attempting NSIS installer..." -ForegroundColor Cyan
cpack -G NSIS -C Release 2>$null
if ($LASTEXITCODE -eq 0) {
    Write-Host "✓ NSIS installer created" -ForegroundColor Green
    $installerType = "NSIS"
} else {
    # Fallback to ZIP
    Write-Host "NSIS not available, creating ZIP package..." -ForegroundColor Yellow
    cpack -G ZIP -C Release
    if ($LASTEXITCODE -eq 0) {
        Write-Host "✓ ZIP package created" -ForegroundColor Green
        $installerType = "ZIP"
    } else {
        Write-Host "✗ Package creation failed" -ForegroundColor Red
        exit 1
    }
}

# List generated packages
Write-Host "`n=== Build Complete ===" -ForegroundColor Green
Write-Host "`nGenerated packages:" -ForegroundColor Cyan
Get-ChildItem -Path . -Filter "AutoCoder-*.*" | ForEach-Object {
    Write-Host "  $_" -ForegroundColor White
    Write-Host "  Size: $([math]::Round($_.Length / 1MB, 2)) MB" -ForegroundColor Gray
}

Write-Host "`n✓ Windows installer build complete!" -ForegroundColor Green
Write-Host "Installer location: $PWD" -ForegroundColor Cyan

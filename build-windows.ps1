# AutoCoder Windows Build Script
# Builds AutoCoder with Qt6 and generates NSIS installer

param(
    [string]$QtPath = "",
    [switch]$Clean = $false
)

Write-Host "========================================" -ForegroundColor Green
Write-Host "AutoCoder Windows Build Script" -ForegroundColor Green
Write-Host "========================================" -ForegroundColor Green
Write-Host ""

# Function to find Qt6 installation
function Find-Qt6 {
    Write-Host "Searching for Qt6 installation..." -ForegroundColor Yellow

    # Common Qt installation locations
    $qtLocations = @(
        "C:\Qt\6.*\msvc*_64",
        "C:\Qt6\6.*\msvc*_64",
        "$env:USERPROFILE\Qt\6.*\msvc*_64",
        "C:\Program Files\Qt\6.*\msvc*_64"
    )

    foreach ($location in $qtLocations) {
        $paths = Get-ChildItem -Path $location -ErrorAction SilentlyContinue | Sort-Object Name -Descending
        if ($paths) {
            $qtPath = $paths[0].FullName
            Write-Host "✓ Found Qt6 at: $qtPath" -ForegroundColor Green
            return $qtPath
        }
    }

    Write-Host "✗ Qt6 not found!" -ForegroundColor Red
    Write-Host ""
    Write-Host "Please install Qt6 from: https://www.qt.io/download-qt-installer" -ForegroundColor Yellow
    Write-Host "Or specify Qt path with: -QtPath 'C:\Qt\6.7.0\msvc2019_64'" -ForegroundColor Yellow
    exit 1
}

# Find or use provided Qt path
if ($QtPath -eq "") {
    $QtPath = Find-Qt6
} else {
    if (-not (Test-Path $QtPath)) {
        Write-Host "✗ Qt path not found: $QtPath" -ForegroundColor Red
        exit 1
    }
    Write-Host "✓ Using Qt6 at: $QtPath" -ForegroundColor Green
}

# Check for Visual Studio
Write-Host "Checking for Visual Studio..." -ForegroundColor Yellow

$vsPath = & "C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe" -latest -property installationPath 2>$null
if ($vsPath) {
    Write-Host "✓ Found Visual Studio at: $vsPath" -ForegroundColor Green
} else {
    Write-Host "✗ Visual Studio not found!" -ForegroundColor Red
    Write-Host "Please install Visual Studio 2019 or 2022 with C++ support" -ForegroundColor Yellow
    exit 1
}

# Detect Visual Studio version
$vsVersion = & "C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe" -latest -property catalog_productLineVersion 2>$null
$generator = switch ($vsVersion) {
    "2022" { "Visual Studio 17 2022" }
    "2019" { "Visual Studio 16 2019" }
    default { "Visual Studio 17 2022" }
}
Write-Host "✓ Using generator: $generator" -ForegroundColor Green

# Check for CMake
Write-Host "Checking for CMake..." -ForegroundColor Yellow
$cmake = Get-Command cmake -ErrorAction SilentlyContinue
if ($cmake) {
    Write-Host "✓ Found CMake: $($cmake.Source)" -ForegroundColor Green
} else {
    Write-Host "✗ CMake not found!" -ForegroundColor Red
    Write-Host "Please install CMake from: https://cmake.org/download/" -ForegroundColor Yellow
    exit 1
}

# Set build directory
$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$buildDir = Join-Path $scriptDir "build-windows"

# Clean build directory if requested
if ($Clean -and (Test-Path $buildDir)) {
    Write-Host "Cleaning build directory..." -ForegroundColor Yellow
    Remove-Item -Path $buildDir -Recurse -Force
}

# Create build directory
Write-Host ""
Write-Host "Setting up build directory..." -ForegroundColor Green
New-Item -ItemType Directory -Path $buildDir -Force | Out-Null
Set-Location $buildDir

# Set environment variables
Write-Host "Configuring environment..." -ForegroundColor Green
$env:CMAKE_PREFIX_PATH = $QtPath
$env:PATH = "$QtPath\bin;$env:PATH"

Write-Host ""
Write-Host "========================================" -ForegroundColor Cyan
Write-Host "Starting Build Process" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

# Configure with CMake
Write-Host "Step 1/3: Configuring with CMake..." -ForegroundColor Yellow
Write-Host ""
try {
    cmake .. `
        -G "$generator" `
        -A x64 `
        -DCMAKE_BUILD_TYPE=Release `
        -DBUILD_INSTALLER=ON `
        -DCMAKE_PREFIX_PATH="$QtPath"

    if ($LASTEXITCODE -ne 0) {
        throw "CMake configuration failed"
    }
    Write-Host ""
    Write-Host "✓ Configuration complete!" -ForegroundColor Green
} catch {
    Write-Host ""
    Write-Host "✗ Configuration failed: $_" -ForegroundColor Red
    exit 1
}

# Build
Write-Host ""
Write-Host "Step 2/3: Building AutoCoder..." -ForegroundColor Yellow
Write-Host "(This may take 3-5 minutes)" -ForegroundColor Gray
Write-Host ""
try {
    cmake --build . --config Release -j

    if ($LASTEXITCODE -ne 0) {
        throw "Build failed"
    }
    Write-Host ""
    Write-Host "✓ Build complete!" -ForegroundColor Green
} catch {
    Write-Host ""
    Write-Host "✗ Build failed: $_" -ForegroundColor Red
    exit 1
}

# Generate installer
Write-Host ""
Write-Host "Step 3/3: Generating NSIS installer..." -ForegroundColor Yellow
Write-Host ""

# Check for NSIS
$nsisPath = Get-Command makensis -ErrorAction SilentlyContinue
if (-not $nsisPath) {
    Write-Host "⚠ NSIS not found in PATH" -ForegroundColor Yellow
    Write-Host "Checking default installation location..." -ForegroundColor Yellow
    $nsisDefault = "C:\Program Files (x86)\NSIS\makensis.exe"
    if (Test-Path $nsisDefault) {
        $env:PATH = "C:\Program Files (x86)\NSIS;$env:PATH"
        Write-Host "✓ Found NSIS" -ForegroundColor Green
    } else {
        Write-Host ""
        Write-Host "✗ NSIS not found!" -ForegroundColor Red
        Write-Host "Download from: https://nsis.sourceforge.io/Download" -ForegroundColor Yellow
        Write-Host ""
        Write-Host "Build succeeded, but installer was not created." -ForegroundColor Yellow
        Write-Host "Executable is at: $buildDir\Release\autocoder.exe" -ForegroundColor Cyan
        exit 0
    }
}

try {
    cpack -C Release -G NSIS

    if ($LASTEXITCODE -ne 0) {
        throw "Installer generation failed"
    }
    Write-Host ""
    Write-Host "✓ Installer generation complete!" -ForegroundColor Green
} catch {
    Write-Host ""
    Write-Host "✗ Installer generation failed: $_" -ForegroundColor Red
    Write-Host "Executable is still available at: $buildDir\Release\autocoder.exe" -ForegroundColor Yellow
    exit 1
}

# Find generated installer
$installer = Get-ChildItem -Path $buildDir -Filter "AutoCoder-*.exe" | Select-Object -First 1

Write-Host ""
Write-Host "========================================" -ForegroundColor Green
Write-Host "✓ BUILD SUCCESSFUL!" -ForegroundColor Green
Write-Host "========================================" -ForegroundColor Green
Write-Host ""

if ($installer) {
    Write-Host "Installer created:" -ForegroundColor Cyan
    Write-Host "  $($installer.FullName)" -ForegroundColor White
    Write-Host ""
    Write-Host "Size: $([math]::Round($installer.Length / 1MB, 2)) MB" -ForegroundColor Gray
    Write-Host ""
    Write-Host "To install AutoCoder, run:" -ForegroundColor Yellow
    Write-Host "  .\$($installer.Name)" -ForegroundColor White
} else {
    Write-Host "Executable created:" -ForegroundColor Cyan
    Write-Host "  $buildDir\Release\autocoder.exe" -ForegroundColor White
}

Write-Host ""
Write-Host "========================================" -ForegroundColor Green
Write-Host ""

# Return to original directory
Set-Location $scriptDir

# Release Process

This document describes how to create and publish releases for AutoCoder.

## Release Checklist

- [ ] Update version numbers in code
- [ ] Update CHANGELOG.md
- [ ] Run all tests
- [ ] Build and test installers locally
- [ ] Update documentation
- [ ] Create git tag
- [ ] Push tag to trigger CI/CD
- [ ] Verify GitHub Release artifacts
- [ ] Announce release

## Version Numbering

AutoCoder uses [Semantic Versioning](https://semver.org/):

- **MAJOR.MINOR.PATCH** (e.g., 1.2.3)
- **MAJOR**: Breaking changes
- **MINOR**: New features (backward compatible)
- **PATCH**: Bug fixes (backward compatible)

## Step-by-Step Release Process

### 1. Prepare the Release

Update version in `CMakeLists.txt`:

```cmake
project(AutoCoder VERSION 1.0.1 LANGUAGES CXX)
```

Update `CHANGELOG.md`:

```markdown
## [1.0.1] - 2025-01-15

### Added
- New feature description

### Fixed
- Bug fix description

### Changed
- Change description
```

### 2. Test Locally

```bash
# Run tests
./scripts/build.sh --tests --clean
cd build && ctest --output-on-failure

# Build installers
./scripts/package-installers.sh

# Test installer (platform-specific)
# See PACKAGING.md for testing instructions
```

### 3. Commit and Tag

```bash
# Commit version updates
git add CMakeLists.txt CHANGELOG.md
git commit -m "chore: Bump version to 1.0.1"

# Create annotated tag
git tag -a v1.0.1 -m "Release version 1.0.1

## What's Changed
- New feature description
- Bug fix description

## Installation
Download installers from the GitHub Release page."

# Push to repository
git push origin main
git push origin v1.0.1
```

### 4. Automated Build Process

GitHub Actions will automatically:

1. Detect the new tag
2. Build for all platforms (Linux, macOS, Windows)
3. Generate installers (DEB, RPM, DMG, NSIS)
4. Create a GitHub Release
5. Upload all installers to the release

Monitor the workflow:
- Go to: `https://github.com/yourusername/autocoder/actions`
- Watch the "Build Release Installers" workflow

### 5. Finalize GitHub Release

Once the workflow completes:

1. Go to: `https://github.com/yourusername/autocoder/releases`
2. Find the auto-generated release
3. Click "Edit"
4. Verify release notes are correct
5. Add additional context if needed:

```markdown
## AutoCoder v1.0.1

### What's New
- Feature improvements
- Bug fixes
- Performance enhancements

### Installation

**Linux (Ubuntu/Debian):**
```bash
wget https://github.com/yourusername/autocoder/releases/download/v1.0.1/AutoCoder-1.0.1-Linux.deb
sudo dpkg -i AutoCoder-1.0.1-Linux.deb
```

**Linux (Fedora/RHEL):**
```bash
wget https://github.com/yourusername/autocoder/releases/download/v1.0.1/AutoCoder-1.0.1-Linux.rpm
sudo dnf install AutoCoder-1.0.1-Linux.rpm
```

**macOS:**
Download and open `AutoCoder-1.0.1-Darwin.dmg`

**Windows:**
Download and run `AutoCoder-1.0.1-win64.exe`

### Full Changelog
See [CHANGELOG.md](https://github.com/yourusername/autocoder/blob/main/CHANGELOG.md)
```

6. Uncheck "This is a pre-release" if stable
7. Click "Publish release"

### 6. Manual Release (Without GitHub Actions)

If you need to create releases manually:

#### Build All Platforms

**Linux:**
```bash
./scripts/package-installers.sh
# Outputs: build-release/AutoCoder-1.0.1-Linux.{deb,rpm}
```

**macOS:**
```bash
./scripts/package-installers.sh
# Output: build-release/AutoCoder-1.0.1-Darwin.dmg
```

**Windows:**
```powershell
.\scripts\package-installers.bat
# Output: build-release\AutoCoder-1.0.1-win64.exe
```

#### Create GitHub Release Manually

1. Go to: `https://github.com/yourusername/autocoder/releases/new`
2. Choose the tag (e.g., `v1.0.1`)
3. Fill in release title: "AutoCoder v1.0.1"
4. Add release notes
5. Drag and drop installer files:
   - `AutoCoder-1.0.1-Linux.deb`
   - `AutoCoder-1.0.1-Linux.rpm`
   - `AutoCoder-1.0.1-Darwin.dmg`
   - `AutoCoder-1.0.1-win64.exe`
6. Click "Publish release"

## Pre-Release / Beta Versions

For beta releases:

```bash
# Tag with pre-release identifier
git tag -a v1.1.0-beta.1 -m "Beta release 1.1.0-beta.1"
git push origin v1.1.0-beta.1
```

In GitHub Release:
- Check "This is a pre-release"
- Add warning about beta status

## Hotfix Releases

For urgent bug fixes:

1. Create hotfix branch from main:
   ```bash
   git checkout -b hotfix/1.0.2 main
   ```

2. Make fixes and commit:
   ```bash
   git commit -m "fix: Critical bug description"
   ```

3. Update version and tag:
   ```bash
   # Update CMakeLists.txt to 1.0.2
   git commit -m "chore: Bump version to 1.0.2"
   git tag -a v1.0.2 -m "Hotfix release 1.0.2"
   ```

4. Merge back to main:
   ```bash
   git checkout main
   git merge hotfix/1.0.2
   git push origin main
   git push origin v1.0.2
   ```

## Post-Release Tasks

### 1. Update Documentation

Update links in README.md to point to latest release:

```markdown
Download the latest version (v1.0.1) from [Releases](https://github.com/yourusername/autocoder/releases/latest)
```

### 2. Announce Release

- Post on project website/blog
- Social media announcement
- Update package managers (if applicable):
  - Homebrew
  - AUR (Arch User Repository)
  - Chocolatey
  - Snap Store
  - Flathub

### 3. Close Milestone

If using GitHub milestones:
1. Go to: `https://github.com/yourusername/autocoder/milestones`
2. Find the milestone for this release
3. Verify all issues are closed
4. Close the milestone

### 4. Plan Next Release

1. Create new milestone for next version
2. Add planned features/fixes to milestone
3. Update project roadmap

## Rollback Procedure

If a critical issue is found after release:

### Option 1: Quick Hotfix

1. Fix the issue
2. Release new patch version (e.g., 1.0.2)
3. Add note to previous release warning about the issue

### Option 2: Delete Release

```bash
# Delete tag locally
git tag -d v1.0.1

# Delete tag remotely
git push origin :refs/tags/v1.0.1

# Delete GitHub Release (manually via web interface)
```

Then fix and re-release with the same version.

## Versioning Strategy

### Major Version (X.0.0)

Breaking changes:
- Major API changes
- Removed features
- Incompatible changes

Example: `2.0.0`

### Minor Version (1.X.0)

New features (backward compatible):
- New functionality
- Enhancements
- Non-breaking changes

Example: `1.1.0`

### Patch Version (1.0.X)

Bug fixes:
- Bug fixes
- Security patches
- Documentation updates

Example: `1.0.1`

## Release Schedule

- **Major releases**: Every 6-12 months
- **Minor releases**: Every 1-3 months
- **Patch releases**: As needed for critical bugs
- **Security releases**: Immediately as needed

## Security Releases

For security vulnerabilities:

1. **Do not** disclose details publicly initially
2. Fix the vulnerability privately
3. Prepare patch release
4. Coordinate disclosure with security team
5. Release patch
6. Publish security advisory
7. Update all affected versions

## Support Timeline

- **Current version**: Full support
- **Previous minor version**: Security updates for 6 months
- **Older versions**: End of life, upgrade recommended

## Continuous Deployment

For automatic releases on every commit to main:

Update `.github/workflows/build-release.yml`:

```yaml
on:
  push:
    branches: [ main ]
    tags:
      - 'v*'
```

This will create draft releases that can be published manually.

## Testing Releases

Before publishing:

1. **Smoke test** each installer
2. **Verify** all features work
3. **Check** for installation/uninstallation issues
4. **Test** on clean systems (use VMs or containers)

## Metrics to Track

After each release:

- Download counts per platform
- Installation success rate
- Critical bugs reported
- User feedback
- Performance metrics

## Resources

- [Semantic Versioning](https://semver.org/)
- [Keep a Changelog](https://keepachangelog.com/)
- [GitHub Releases](https://docs.github.com/en/repositories/releasing-projects-on-github)
- [CPack Documentation](https://cmake.org/cmake/help/latest/module/CPack.html)

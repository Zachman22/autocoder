# Complete v1.1.0 Release Instructions

## Current Status ✅

- ✅ Version bumped to 1.1.0 in CMakeLists.txt
- ✅ CHANGELOG.md updated with v1.1.0 release notes
- ✅ Changes committed to branch `claude/make-releases-B82Vy`
- ✅ Branch pushed to remote
- ✅ Tag `v1.1.0` created locally
- ⚠️ Tag NOT yet pushed (403 permission error)

## Option 1: Automatic Release (Recommended)

This will trigger the GitHub Actions workflow to build all installers automatically.

### Step 1: Merge the Branch

First, merge the `claude/make-releases-B82Vy` branch to your main branch:

```bash
# Either create a PR and merge via GitHub UI, or:
git checkout main  # or your default branch
git merge claude/make-releases-B82Vy
```

### Step 2: Push the Tag

Push the v1.1.0 tag to trigger the automated build:

```bash
git push origin v1.1.0
```

Or create and push the tag fresh:

```bash
git tag -a v1.1.0 -m "Release version 1.1.0

## What's New in v1.1.0

### Added
- Comprehensive installer generation system with automated packaging script
- GitHub Actions CI/CD workflow for automated release builds
- Multi-platform installer support (DEB, RPM, DMG, NSIS)
- Quick start guide for installer generation
- Detailed release process documentation
- Enhanced packaging documentation

### Improved
- Automated build and release workflow for all platforms
- Cross-platform installer consistency
- Release process automation and documentation"

git push origin v1.1.0
```

### Step 3: Monitor the Workflow

1. Go to: https://github.com/Zachman22/autocoder/actions
2. Watch the "Build Release Installers" workflow
3. Wait for all jobs to complete (Linux, macOS, Windows builds)

### Step 4: Verify the Release

1. Go to: https://github.com/Zachman22/autocoder/releases
2. Find the auto-generated v1.1.0 release
3. Verify all installers are attached:
   - AutoCoder-1.1.0-Linux.deb
   - AutoCoder-1.1.0-Linux.rpm
   - AutoCoder-1.1.0-Darwin.dmg
   - AutoCoder-1.1.0-win64.exe

## Option 2: Manual Workflow Trigger

If pushing the tag still fails, you can manually trigger the workflow:

1. Go to: https://github.com/Zachman22/autocoder/actions/workflows/build-release.yml
2. Click "Run workflow"
3. Select the branch: `claude/make-releases-B82Vy` (or `main` after merge)
4. Click "Run workflow"

Note: This will build the installers but won't automatically create the release. You'll need to create it manually (see Option 3).

## Option 3: Manual Release Creation

If automatic methods don't work, create the release manually:

### Step 1: Build Installers Locally (Optional)

If you want to test locally first:

```bash
./scripts/package-installers.sh
```

This creates installers in `build-release/` directory.

### Step 2: Create GitHub Release

1. Go to: https://github.com/Zachman22/autocoder/releases/new
2. Choose tag: `v1.1.0` (create new tag if needed)
3. Target: `main` (or your default branch)
4. Release title: **AutoCoder v1.1.0**
5. Description:

```markdown
## What's New in v1.1.0

### Added
- Comprehensive installer generation system with automated packaging script
- GitHub Actions CI/CD workflow for automated release builds
- Multi-platform installer support (DEB, RPM, DMG, NSIS)
- Quick start guide for installer generation (QUICK_START_INSTALLERS.md)
- Detailed release process documentation (RELEASE.md)
- Enhanced packaging documentation (PACKAGING.md)

### Improved
- Automated build and release workflow for all platforms
- Cross-platform installer consistency
- Release process automation and documentation

## Installation

### Linux (Ubuntu/Debian)
```bash
wget https://github.com/Zachman22/autocoder/releases/download/v1.1.0/AutoCoder-1.1.0-Linux.deb
sudo dpkg -i AutoCoder-1.1.0-Linux.deb
```

### Linux (Fedora/RHEL)
```bash
wget https://github.com/Zachman22/autocoder/releases/download/v1.1.0/AutoCoder-1.1.0-Linux.rpm
sudo dnf install AutoCoder-1.1.0-Linux.rpm
```

### macOS
Download and open `AutoCoder-1.1.0-Darwin.dmg`

### Windows
Download and run `AutoCoder-1.1.0-win64.exe`

## Full Changelog
See [CHANGELOG.md](https://github.com/Zachman22/autocoder/blob/main/CHANGELOG.md)
```

6. Attach installer files (if built locally or from Actions artifacts)
7. Uncheck "This is a pre-release"
8. Click "Publish release"

## Troubleshooting

### Tag Push Fails with 403
- Ensure you have push permissions to the repository
- Try pushing from the main branch after merging
- Check if branch protection rules are blocking tag pushes

### Workflow Doesn't Trigger
- Verify the tag name matches the pattern `v*`
- Check GitHub Actions are enabled for the repository
- Try manually triggering via workflow_dispatch

### Installers Not Building
- Check workflow logs for errors
- Verify dependencies are available in CI environment
- Ensure CMakeLists.txt has correct version (1.1.0)

## Next Steps After Release

1. ✅ Announce the release
2. ✅ Update documentation links to point to v1.1.0
3. ✅ Close the v1.1.0 milestone (if using milestones)
4. ✅ Plan v1.2.0 features

---

**Current branch**: `claude/make-releases-B82Vy`
**Tag status**: Created locally, needs to be pushed
**Recommended action**: Follow Option 1 above

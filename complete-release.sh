#!/bin/bash
# AutoCoder v1.1.0 Release Completion Script
# This script completes the release by pushing the tag to trigger GitHub Actions

set -e

echo "========================================="
echo "AutoCoder v1.1.0 Release Completion"
echo "========================================="
echo ""

# Check if tag exists locally
if ! git tag -l | grep -q "^v1.1.0$"; then
    echo "❌ Error: Tag v1.1.0 not found locally"
    echo "Creating tag now..."
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
fi

echo "✅ Tag v1.1.0 exists locally"
echo ""

# Push the tag
echo "🚀 Pushing tag v1.1.0 to origin..."
echo ""

if git push origin v1.1.0; then
    echo ""
    echo "========================================="
    echo "✅ SUCCESS! Tag pushed successfully"
    echo "========================================="
    echo ""
    echo "GitHub Actions is now building your release!"
    echo ""
    echo "📋 What happens next:"
    echo "  1. GitHub Actions builds installers for all platforms"
    echo "  2. Creates GitHub Release automatically"
    echo "  3. Uploads all installers to the release"
    echo ""
    echo "🔗 Monitor progress:"
    echo "  • Workflow: https://github.com/Zachman22/autocoder/actions"
    echo "  • Release:  https://github.com/Zachman22/autocoder/releases"
    echo ""
    echo "📦 Expected installers:"
    echo "  • AutoCoder-1.1.0-Linux.deb"
    echo "  • AutoCoder-1.1.0-Linux.rpm"
    echo "  • AutoCoder-1.1.0-Darwin.dmg"
    echo "  • AutoCoder-1.1.0-win64.exe"
    echo ""
    echo "⏱️  Build time: ~15-20 minutes"
    echo ""
else
    EXIT_CODE=$?
    echo ""
    echo "========================================="
    echo "❌ FAILED: Could not push tag"
    echo "========================================="
    echo ""
    echo "This may be due to:"
    echo "  • Network connectivity issues"
    echo "  • Repository permission restrictions"
    echo "  • Branch protection rules"
    echo ""
    echo "🔧 Alternative: Manual tag creation"
    echo ""
    echo "Option 1: Via GitHub Web Interface"
    echo "  1. Go to: https://github.com/Zachman22/autocoder/releases/new"
    echo "  2. Create tag: v1.1.0"
    echo "  3. Target: claude/make-releases-B82Vy"
    echo "  4. Publish release"
    echo ""
    echo "Option 2: Trigger workflow manually"
    echo "  1. Go to: https://github.com/Zachman22/autocoder/actions/workflows/build-release.yml"
    echo "  2. Click 'Run workflow'"
    echo "  3. Select branch: claude/make-releases-B82Vy"
    echo "  4. Click 'Run workflow'"
    echo ""
    exit $EXIT_CODE
fi

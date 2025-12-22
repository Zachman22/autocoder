#include "gui/theme_manager.h"

namespace AutoCoder {
namespace GUI {

ThemeManager* ThemeManager::instance_ = nullptr;

ThemeManager::ThemeManager() {
    loadDefaultThemes();
}

ThemeManager::~ThemeManager() {}

ThemeManager* ThemeManager::getInstance() {
    if (!instance_) {
        instance_ = new ThemeManager();
    }
    return instance_;
}

void ThemeManager::loadTheme(const QString& theme_name) {}
void ThemeManager::saveTheme(const QString& theme_name) {}
Theme ThemeManager::getCurrentTheme() const { return current_theme_; }
void ThemeManager::setCurrentTheme(const QString& theme_name) {}
QStringList ThemeManager::getAvailableThemes() const { return QStringList(); }
void ThemeManager::addTheme(const Theme& theme) {}
void ThemeManager::removeTheme(const QString& theme_name) {}
QColor ThemeManager::getColor(const QString& key) const { return QColor(); }
QString ThemeManager::getStyle(const QString& key) const { return QString(); }
QString ThemeManager::getStyleSheet() const { return QString(); }
void ThemeManager::importTheme(const QString& filepath) {}
void ThemeManager::exportTheme(const QString& theme_name, const QString& filepath) {}
void ThemeManager::loadDefaultThemes() {}

} // namespace GUI
} // namespace AutoCoder

#ifndef AUTOCODER_THEME_MANAGER_H
#define AUTOCODER_THEME_MANAGER_H

#include <QString>
#include <QColor>
#include <QMap>
#include <memory>

namespace AutoCoder {
namespace GUI {

struct Theme {
    QString name;
    QMap<QString, QColor> colors;
    QMap<QString, QString> styles;
    QString stylesheet;
};

class ThemeManager {
public:
    ThemeManager();
    ~ThemeManager();

    static ThemeManager* getInstance();

    void loadTheme(const QString& theme_name);
    void saveTheme(const QString& theme_name);

    Theme getCurrentTheme() const;
    void setCurrentTheme(const QString& theme_name);

    QStringList getAvailableThemes() const;
    void addTheme(const Theme& theme);
    void removeTheme(const QString& theme_name);

    QColor getColor(const QString& key) const;
    QString getStyle(const QString& key) const;
    QString getStyleSheet() const;

    void importTheme(const QString& filepath);
    void exportTheme(const QString& theme_name, const QString& filepath);

private:
    void loadDefaultThemes();

    static ThemeManager* instance_;
    QMap<QString, Theme> themes_;
    Theme current_theme_;
};

} // namespace GUI
} // namespace AutoCoder

#endif // AUTOCODER_THEME_MANAGER_H

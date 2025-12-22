#ifndef AUTOCODER_GUI_BUILDER_H
#define AUTOCODER_GUI_BUILDER_H

#include <string>
#include <vector>
#include <map>
#include <memory>

namespace AutoCoder {
namespace GUIMaker {

enum class WidgetType {
    WINDOW,
    BUTTON,
    LABEL,
    TEXTBOX,
    CHECKBOX,
    RADIOBUTTON,
    COMBOBOX,
    LISTBOX,
    PANEL,
    MENUBAR,
    TOOLBAR,
    STATUSBAR,
    TREEVIEW,
    TABLEVIEW,
    CUSTOM
};

struct Widget {
    std::string id;
    WidgetType type;
    std::string name;
    int x, y, width, height;
    std::map<std::string, std::string> properties;
    std::vector<std::shared_ptr<Widget>> children;
    std::string event_handler_code;
};

struct GUIProject {
    std::string name;
    std::string target_framework;
    std::shared_ptr<Widget> root_widget;
    std::map<std::string, std::string> global_styles;
    std::vector<std::string> resources;
};

class GUIBuilder {
public:
    GUIBuilder();
    ~GUIBuilder();

    GUIProject createProject(const std::string& name, const std::string& framework);
    bool loadProject(const std::string& filepath);
    bool saveProject(const GUIProject& project, const std::string& filepath);

    std::shared_ptr<Widget> createWidget(WidgetType type, const std::string& name);
    void addWidget(std::shared_ptr<Widget> parent, std::shared_ptr<Widget> child);
    void removeWidget(std::shared_ptr<Widget> widget);

    void setWidgetProperty(std::shared_ptr<Widget> widget, const std::string& key, const std::string& value);
    std::string getWidgetProperty(std::shared_ptr<Widget> widget, const std::string& key);

    void setEventHandler(std::shared_ptr<Widget> widget, const std::string& event, const std::string& handler);

    void applyTheme(GUIProject& project, const std::string& theme_name);
    void setGlobalStyle(GUIProject& project, const std::string& key, const std::string& value);

    std::vector<std::string> getSupportedFrameworks() const;
    std::vector<WidgetType> getSupportedWidgets() const;

private:
    int next_widget_id_;
};

} // namespace GUIMaker
} // namespace AutoCoder

#endif // AUTOCODER_GUI_BUILDER_H

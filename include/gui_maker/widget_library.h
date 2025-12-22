#ifndef AUTOCODER_WIDGET_LIBRARY_H
#define AUTOCODER_WIDGET_LIBRARY_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "gui_builder.h"

namespace AutoCoder {
namespace GUIMaker {

struct WidgetTemplate {
    std::string name;
    WidgetType base_type;
    std::map<std::string, std::string> default_properties;
    std::string preview_image;
    std::string description;
};

class WidgetLibrary {
public:
    WidgetLibrary();
    ~WidgetLibrary();

    void registerWidget(const WidgetTemplate& widget_template);
    void unregisterWidget(const std::string& widget_name);

    WidgetTemplate getTemplate(const std::string& widget_name);
    std::vector<WidgetTemplate> getAllTemplates() const;

    std::vector<WidgetTemplate> searchWidgets(const std::string& query);
    std::vector<WidgetTemplate> getWidgetsByCategory(const std::string& category);

    bool loadLibrary(const std::string& filepath);
    bool saveLibrary(const std::string& filepath);

    void importUserWidget(const std::string& filepath);
    void exportUserWidget(const std::string& widget_name, const std::string& filepath);

private:
    std::map<std::string, WidgetTemplate> templates_;
    std::map<std::string, std::vector<std::string>> categories_;
};

} // namespace GUIMaker
} // namespace AutoCoder

#endif // AUTOCODER_WIDGET_LIBRARY_H

#ifndef AUTOCODER_LAYOUT_MANAGER_H
#define AUTOCODER_LAYOUT_MANAGER_H

#include <string>
#include <vector>
#include <memory>
#include "gui_builder.h"

namespace AutoCoder {
namespace GUIMaker {

enum class LayoutType {
    ABSOLUTE,
    FLOW,
    GRID,
    BORDER,
    BOX,
    FORM,
    STACK,
    CUSTOM
};

struct LayoutProperties {
    LayoutType type;
    int spacing;
    int padding;
    std::string alignment;
    bool auto_resize;
    std::map<std::string, std::string> custom_properties;
};

class LayoutManager {
public:
    LayoutManager();
    ~LayoutManager();

    void setLayout(std::shared_ptr<Widget> container, const LayoutProperties& properties);
    LayoutProperties getLayout(std::shared_ptr<Widget> container);

    void arrangeWidgets(std::shared_ptr<Widget> container);
    void autoArrange(std::shared_ptr<Widget> container, LayoutType layout_type);

    void alignWidgets(std::vector<std::shared_ptr<Widget>> widgets, const std::string& alignment);
    void distributeWidgets(std::vector<std::shared_ptr<Widget>> widgets, const std::string& direction);

    void snapToGrid(std::shared_ptr<Widget> widget, int grid_size);
    void setGridSize(int size);

    void enableResponsiveLayout(bool enable);
    void setBreakpoints(const std::map<std::string, int>& breakpoints);

private:
    void calculateAbsoluteLayout(std::shared_ptr<Widget> container);
    void calculateFlowLayout(std::shared_ptr<Widget> container);
    void calculateGridLayout(std::shared_ptr<Widget> container);

    int grid_size_;
    bool responsive_enabled_;
    std::map<std::string, int> breakpoints_;
};

} // namespace GUIMaker
} // namespace AutoCoder

#endif // AUTOCODER_LAYOUT_MANAGER_H

#ifndef AUTOCODER_CODE_EXPORTER_H
#define AUTOCODER_CODE_EXPORTER_H

#include <string>
#include <map>
#include "gui_builder.h"

namespace AutoCoder {
namespace GUIMaker {

struct ExportOptions {
    std::string target_language;
    std::string target_framework;
    bool include_comments;
    bool generate_separate_files;
    std::string output_directory;
    std::map<std::string, std::string> custom_options;
};

struct ExportResult {
    std::map<std::string, std::string> files;
    std::vector<std::string> warnings;
    bool success;
    std::string error_message;
};

class CodeExporter {
public:
    CodeExporter();
    ~CodeExporter();

    ExportResult exportProject(const GUIProject& project, const ExportOptions& options);

    std::string generateCode(std::shared_ptr<Widget> widget, const std::string& language);
    std::string generateUIFile(const GUIProject& project, const std::string& format);
    std::string generateResourceFile(const GUIProject& project);

    void registerExporter(const std::string& framework, void* exporter_function);

    std::vector<std::string> getSupportedFormats() const;

private:
    std::string exportToQt(const GUIProject& project, const ExportOptions& options);
    std::string exportToWxWidgets(const GUIProject& project, const ExportOptions& options);
    std::string exportToGTK(const GUIProject& project, const ExportOptions& options);
    std::string exportToHTML(const GUIProject& project, const ExportOptions& options);

    std::string widgetToCode(std::shared_ptr<Widget> widget, const std::string& language, int indent_level);

    std::map<std::string, void*> custom_exporters_;
};

} // namespace GUIMaker
} // namespace AutoCoder

#endif // AUTOCODER_CODE_EXPORTER_H

#ifndef AUTOCODER_SETTINGS_DIALOG_H
#define AUTOCODER_SETTINGS_DIALOG_H

#include <QDialog>
#include <QTabWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QSpinBox>

namespace AutoCoder {
namespace GUI {

class SettingsDialog : public QDialog {
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget* parent = nullptr);
    ~SettingsDialog();

    void loadSettings();
    void saveSettings();

private slots:
    void onOKClicked();
    void onCancelClicked();
    void onApplyClicked();
    void onBrowseApiKeyClicked();
    void onTestConnectionClicked();

private:
    void setupUI();
    void createGeneralTab();
    void createEditorTab();
    void createAITab();
    void createDebuggerTab();
    void createCompilerTab();

    QTabWidget* tab_widget_;

    // General settings
    QComboBox* theme_combo_;
    QComboBox* language_combo_;
    QCheckBox* auto_save_check_;

    // Editor settings
    QSpinBox* font_size_spin_;
    QLineEdit* font_family_edit_;
    QCheckBox* line_numbers_check_;
    QCheckBox* auto_indent_check_;
    QCheckBox* auto_complete_check_;

    // AI settings
    QLineEdit* api_key_edit_;
    QLineEdit* api_endpoint_edit_;
    QComboBox* model_combo_;
    QSpinBox* max_tokens_spin_;
    QDoubleSpinBox* temperature_spin_;

    // Debugger settings
    QCheckBox* continuous_debug_check_;
    QSpinBox* scan_interval_spin_;
    QCheckBox* auto_fix_check_;

    // Compiler settings
    QComboBox* compiler_combo_;
    QLineEdit* compiler_path_edit_;
    QComboBox* optimization_combo_;
    QCheckBox* debug_symbols_check_;
};

} // namespace GUI
} // namespace AutoCoder

#endif // AUTOCODER_SETTINGS_DIALOG_H

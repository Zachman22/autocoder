#ifndef AUTOCODER_OUTPUT_PANEL_H
#define AUTOCODER_OUTPUT_PANEL_H

#include <QWidget>
#include <QTextEdit>
#include <QTabWidget>
#include <QPushButton>

namespace AutoCoder {
namespace GUI {

class OutputPanel : public QWidget {
    Q_OBJECT

public:
    explicit OutputPanel(QWidget* parent = nullptr);
    ~OutputPanel();

    void addBuildOutput(const QString& output);
    void addDebugOutput(const QString& output);
    void addAIOutput(const QString& output);
    void addGeneralOutput(const QString& output);

    void clearBuildOutput();
    void clearDebugOutput();
    void clearAIOutput();
    void clearGeneralOutput();
    void clearAll();

    void setCurrentTab(int index);
    int getCurrentTab() const;

signals:
    void outputCleared(const QString& tab_name);

private slots:
    void onClearClicked();
    void onCopyClicked();
    void onSaveClicked();

private:
    void setupUI();

    QTabWidget* tab_widget_;
    QTextEdit* build_output_;
    QTextEdit* debug_output_;
    QTextEdit* ai_output_;
    QTextEdit* general_output_;

    QPushButton* clear_button_;
    QPushButton* copy_button_;
    QPushButton* save_button_;
};

} // namespace GUI
} // namespace AutoCoder

#endif // AUTOCODER_OUTPUT_PANEL_H

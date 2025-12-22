#ifndef AUTOCODER_MAIN_WINDOW_H
#define AUTOCODER_MAIN_WINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QDockWidget>
#include <memory>

namespace AutoCoder {
namespace GUI {

class CodeEditor;
class ChatPanel;
class DebuggerPanel;
class OutputPanel;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void initialize();

protected:
    void closeEvent(QCloseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private slots:
    void onNewProject();
    void onOpenProject();
    void onSaveProject();
    void onSaveAs();
    void onExit();

    void onUndo();
    void onRedo();
    void onCut();
    void onCopy();
    void onPaste();
    void onFind();
    void onReplace();

    void onCompile();
    void onRun();
    void onDebug();
    void onStop();

    void onGenerateCode();
    void onRefactorCode();
    void onFormatCode();

    void onSettings();
    void onAbout();

    void onChatMessageSent(const QString& message);
    void onDebuggerStateChanged(const QString& state);

private:
    void createMenus();
    void createToolbars();
    void createDockWidgets();
    void createStatusBar();
    void createConnections();

    void loadSettings();
    void saveSettings();

    CodeEditor* code_editor_;
    ChatPanel* chat_panel_;
    DebuggerPanel* debugger_panel_;
    OutputPanel* output_panel_;

    QMenuBar* menu_bar_;
    QToolBar* file_toolbar_;
    QToolBar* edit_toolbar_;
    QToolBar* build_toolbar_;
    QStatusBar* status_bar_;

    QString current_project_path_;
    bool is_modified_;
};

} // namespace GUI
} // namespace AutoCoder

#endif // AUTOCODER_MAIN_WINDOW_H

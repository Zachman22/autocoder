#include "gui/main_window.h"
#include "gui/code_editor.h"
#include "gui/chat_panel.h"
#include "gui/debugger_panel.h"
#include "gui/output_panel.h"
#include <QMenuBar>
#include <QToolBar>
#include <QDockWidget>
#include <QSplitter>
#include <QMessageBox>

namespace AutoCoder {
namespace GUI {

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , is_modified_(false) {
    setWindowTitle("AutoCoder - Self-Improving AI Code Generator");
    resize(1400, 900);
}

MainWindow::~MainWindow() {}

void MainWindow::initialize() {
    // Create central widget
    code_editor_ = new CodeEditor(this);
    setCentralWidget(code_editor_);

    createMenus();
    createToolbars();
    createDockWidgets();
    createStatusBar();
    createConnections();

    loadSettings();
}

void MainWindow::createMenus() {
    // File menu
    QMenu* fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction("&New Project", this, &MainWindow::onNewProject, QKeySequence::New);
    fileMenu->addAction("&Open Project", this, &MainWindow::onOpenProject, QKeySequence::Open);
    fileMenu->addAction("&Save", this, &MainWindow::onSaveProject, QKeySequence::Save);
    fileMenu->addAction("Save &As", this, &MainWindow::onSaveAs);
    fileMenu->addSeparator();
    fileMenu->addAction("E&xit", this, &MainWindow::onExit, QKeySequence::Quit);

    // Edit menu
    QMenu* editMenu = menuBar()->addMenu("&Edit");
    editMenu->addAction("&Undo", this, &MainWindow::onUndo, QKeySequence::Undo);
    editMenu->addAction("&Redo", this, &MainWindow::onRedo, QKeySequence::Redo);
    editMenu->addSeparator();
    editMenu->addAction("Cu&t", this, &MainWindow::onCut, QKeySequence::Cut);
    editMenu->addAction("&Copy", this, &MainWindow::onCopy, QKeySequence::Copy);
    editMenu->addAction("&Paste", this, &MainWindow::onPaste, QKeySequence::Paste);
    editMenu->addSeparator();
    editMenu->addAction("&Find", this, &MainWindow::onFind, QKeySequence::Find);
    editMenu->addAction("&Replace", this, &MainWindow::onReplace, QKeySequence::Replace);

    // Build menu
    QMenu* buildMenu = menuBar()->addMenu("&Build");
    buildMenu->addAction("&Compile", this, &MainWindow::onCompile, QKeySequence("F7"));
    buildMenu->addAction("&Run", this, &MainWindow::onRun, QKeySequence("F5"));
    buildMenu->addAction("&Debug", this, &MainWindow::onDebug, QKeySequence("F8"));
    buildMenu->addAction("&Stop", this, &MainWindow::onStop, QKeySequence("Shift+F5"));

    // AI menu
    QMenu* aiMenu = menuBar()->addMenu("&AI");
    aiMenu->addAction("&Generate Code", this, &MainWindow::onGenerateCode, QKeySequence("Ctrl+G"));
    aiMenu->addAction("&Refactor Code", this, &MainWindow::onRefactorCode, QKeySequence("Ctrl+R"));
    aiMenu->addAction("&Format Code", this, &MainWindow::onFormatCode, QKeySequence("Ctrl+Shift+F"));

    // Tools menu
    QMenu* toolsMenu = menuBar()->addMenu("&Tools");
    toolsMenu->addAction("&Settings", this, &MainWindow::onSettings, QKeySequence("Ctrl+,"));

    // Help menu
    QMenu* helpMenu = menuBar()->addMenu("&Help");
    helpMenu->addAction("&About", this, &MainWindow::onAbout);
}

void MainWindow::createToolbars() {
    file_toolbar_ = addToolBar("File");
    file_toolbar_->setObjectName("FileToolbar");

    edit_toolbar_ = addToolBar("Edit");
    edit_toolbar_->setObjectName("EditToolbar");

    build_toolbar_ = addToolBar("Build");
    build_toolbar_->setObjectName("BuildToolbar");
}

void MainWindow::createDockWidgets() {
    // Chat panel
    QDockWidget* chatDock = new QDockWidget("AI Chat", this);
    chat_panel_ = new ChatPanel(this);
    chatDock->setWidget(chat_panel_);
    addDockWidget(Qt::RightDockWidgetArea, chatDock);

    // Debugger panel
    QDockWidget* debuggerDock = new QDockWidget("Debugger", this);
    debugger_panel_ = new DebuggerPanel(this);
    debuggerDock->setWidget(debugger_panel_);
    addDockWidget(Qt::BottomDockWidgetArea, debuggerDock);

    // Output panel
    QDockWidget* outputDock = new QDockWidget("Output", this);
    output_panel_ = new OutputPanel(this);
    outputDock->setWidget(output_panel_);
    addDockWidget(Qt::BottomDockWidgetArea, outputDock);

    tabifyDockWidget(debuggerDock, outputDock);
}

void MainWindow::createStatusBar() {
    statusBar()->showMessage("Ready");
}

void MainWindow::createConnections() {
    connect(chat_panel_, &ChatPanel::messageSent, this, &MainWindow::onChatMessageSent);
}

void MainWindow::loadSettings() {}
void MainWindow::saveSettings() {}

void MainWindow::closeEvent(QCloseEvent* event) {
    saveSettings();
    QMainWindow::closeEvent(event);
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    QMainWindow::keyPressEvent(event);
}

// Slots
void MainWindow::onNewProject() { statusBar()->showMessage("New Project", 2000); }
void MainWindow::onOpenProject() { statusBar()->showMessage("Open Project", 2000); }
void MainWindow::onSaveProject() { statusBar()->showMessage("Save Project", 2000); }
void MainWindow::onSaveAs() {}
void MainWindow::onExit() { close(); }

void MainWindow::onUndo() {}
void MainWindow::onRedo() {}
void MainWindow::onCut() {}
void MainWindow::onCopy() {}
void MainWindow::onPaste() {}
void MainWindow::onFind() {}
void MainWindow::onReplace() {}

void MainWindow::onCompile() {
    output_panel_->addBuildOutput("Compiling...\n");
    statusBar()->showMessage("Compiling", 2000);
}

void MainWindow::onRun() {
    statusBar()->showMessage("Running", 2000);
}

void MainWindow::onDebug() {
    debugger_panel_->setDebuggerState("Running");
    statusBar()->showMessage("Debugging", 2000);
}

void MainWindow::onStop() {
    debugger_panel_->setDebuggerState("Stopped");
    statusBar()->showMessage("Stopped", 2000);
}

void MainWindow::onGenerateCode() {
    statusBar()->showMessage("Generating code...", 2000);
}

void MainWindow::onRefactorCode() {}
void MainWindow::onFormatCode() {}
void MainWindow::onSettings() {}

void MainWindow::onAbout() {
    QMessageBox::about(this, "About AutoCoder",
        "AutoCoder v1.0\n\n"
        "Self-Improving AI-Powered Code Generator\n"
        "Powered by DeepSeeker 6.7b\n\n"
        "Features:\n"
        "- Continuous debugging\n"
        "- Multi-language support\n"
        "- AI-powered code generation\n"
        "- Integrated compiler\n"
        "- GUI builder\n");
}

void MainWindow::onChatMessageSent(const QString& message) {
    chat_panel_->addMessage("You", message);
    output_panel_->addAIOutput("Processing: " + message + "\n");
}

void MainWindow::onDebuggerStateChanged(const QString& state) {
    statusBar()->showMessage("Debugger: " + state);
}

} // namespace GUI
} // namespace AutoCoder

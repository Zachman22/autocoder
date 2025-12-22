#include "gui/output_panel.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

namespace AutoCoder {
namespace GUI {

OutputPanel::OutputPanel(QWidget* parent) : QWidget(parent) {
    setupUI();
}

OutputPanel::~OutputPanel() {}

void OutputPanel::setupUI() {
    QVBoxLayout* layout = new QVBoxLayout(this);

    tab_widget_ = new QTabWidget(this);

    build_output_ = new QTextEdit(this);
    build_output_->setReadOnly(true);
    tab_widget_->addTab(build_output_, "Build");

    debug_output_ = new QTextEdit(this);
    debug_output_->setReadOnly(true);
    tab_widget_->addTab(debug_output_, "Debug");

    ai_output_ = new QTextEdit(this);
    ai_output_->setReadOnly(true);
    tab_widget_->addTab(ai_output_, "AI");

    general_output_ = new QTextEdit(this);
    general_output_->setReadOnly(true);
    tab_widget_->addTab(general_output_, "General");

    layout->addWidget(tab_widget_);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    clear_button_ = new QPushButton("Clear", this);
    copy_button_ = new QPushButton("Copy", this);
    save_button_ = new QPushButton("Save", this);

    connect(clear_button_, &QPushButton::clicked, this, &OutputPanel::onClearClicked);
    connect(copy_button_, &QPushButton::clicked, this, &OutputPanel::onCopyClicked);
    connect(save_button_, &QPushButton::clicked, this, &OutputPanel::onSaveClicked);

    buttonLayout->addWidget(clear_button_);
    buttonLayout->addWidget(copy_button_);
    buttonLayout->addWidget(save_button_);
    buttonLayout->addStretch();

    layout->addLayout(buttonLayout);
    setLayout(layout);
}

void OutputPanel::addBuildOutput(const QString& output) { build_output_->append(output); }
void OutputPanel::addDebugOutput(const QString& output) { debug_output_->append(output); }
void OutputPanel::addAIOutput(const QString& output) { ai_output_->append(output); }
void OutputPanel::addGeneralOutput(const QString& output) { general_output_->append(output); }

void OutputPanel::clearBuildOutput() { build_output_->clear(); }
void OutputPanel::clearDebugOutput() { debug_output_->clear(); }
void OutputPanel::clearAIOutput() { ai_output_->clear(); }
void OutputPanel::clearGeneralOutput() { general_output_->clear(); }
void OutputPanel::clearAll() {
    clearBuildOutput();
    clearDebugOutput();
    clearAIOutput();
    clearGeneralOutput();
}

void OutputPanel::setCurrentTab(int index) { tab_widget_->setCurrentIndex(index); }
int OutputPanel::getCurrentTab() const { return tab_widget_->currentIndex(); }

void OutputPanel::onClearClicked() {
    int index = tab_widget_->currentIndex();
    switch (index) {
        case 0: clearBuildOutput(); break;
        case 1: clearDebugOutput(); break;
        case 2: clearAIOutput(); break;
        case 3: clearGeneralOutput(); break;
    }
}

void OutputPanel::onCopyClicked() {}
void OutputPanel::onSaveClicked() {}

} // namespace GUI
} // namespace AutoCoder

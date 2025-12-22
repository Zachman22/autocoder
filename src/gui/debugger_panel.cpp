#include "gui/debugger_panel.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

namespace AutoCoder {
namespace GUI {

DebuggerPanel::DebuggerPanel(QWidget* parent) : QWidget(parent) {
    setupUI();
}

DebuggerPanel::~DebuggerPanel() {}

void DebuggerPanel::setupUI() {
    QVBoxLayout* layout = new QVBoxLayout(this);

    state_label_ = new QLabel("Debugger: Stopped", this);
    layout->addWidget(state_label_);

    QHBoxLayout* controlLayout = new QHBoxLayout();
    start_button_ = new QPushButton("Start", this);
    stop_button_ = new QPushButton("Stop", this);
    pause_button_ = new QPushButton("Pause", this);
    resume_button_ = new QPushButton("Resume", this);
    step_into_button_ = new QPushButton("Step Into", this);
    step_over_button_ = new QPushButton("Step Over", this);
    step_out_button_ = new QPushButton("Step Out", this);

    connect(start_button_, &QPushButton::clicked, this, &DebuggerPanel::onStartClicked);
    connect(stop_button_, &QPushButton::clicked, this, &DebuggerPanel::onStopClicked);
    connect(pause_button_, &QPushButton::clicked, this, &DebuggerPanel::onPauseClicked);
    connect(resume_button_, &QPushButton::clicked, this, &DebuggerPanel::onResumeClicked);

    controlLayout->addWidget(start_button_);
    controlLayout->addWidget(stop_button_);
    controlLayout->addWidget(pause_button_);
    controlLayout->addWidget(resume_button_);
    controlLayout->addWidget(step_into_button_);
    controlLayout->addWidget(step_over_button_);
    controlLayout->addWidget(step_out_button_);

    layout->addLayout(controlLayout);

    call_stack_tree_ = new QTreeWidget(this);
    call_stack_tree_->setHeaderLabel("Call Stack");
    layout->addWidget(call_stack_tree_);

    variables_table_ = new QTableWidget(this);
    variables_table_->setColumnCount(2);
    variables_table_->setHorizontalHeaderLabels({"Variable", "Value"});
    layout->addWidget(variables_table_);

    breakpoints_tree_ = new QTreeWidget(this);
    breakpoints_tree_->setHeaderLabel("Breakpoints");
    layout->addWidget(breakpoints_tree_);

    setLayout(layout);
    updateControlButtons();
}

void DebuggerPanel::updateCallStack(const QStringList& frames) {
    call_stack_tree_->clear();
    for (const auto& frame : frames) {
        call_stack_tree_->addTopLevelItem(new QTreeWidgetItem(QStringList() << frame));
    }
}

void DebuggerPanel::updateVariables(const QMap<QString, QString>& variables) {
    variables_table_->setRowCount(variables.size());
    int row = 0;
    for (auto it = variables.begin(); it != variables.end(); ++it) {
        variables_table_->setItem(row, 0, new QTableWidgetItem(it.key()));
        variables_table_->setItem(row, 1, new QTableWidgetItem(it.value()));
        row++;
    }
}

void DebuggerPanel::updateBreakpoints(const QStringList& breakpoints) {
    breakpoints_tree_->clear();
    for (const auto& bp : breakpoints) {
        breakpoints_tree_->addTopLevelItem(new QTreeWidgetItem(QStringList() << bp));
    }
}

void DebuggerPanel::setDebuggerState(const QString& state) {
    current_state_ = state;
    state_label_->setText("Debugger: " + state);
    updateControlButtons();
}

void DebuggerPanel::highlightCurrentFrame(int frame_number) {}
void DebuggerPanel::updateControlButtons() {}

void DebuggerPanel::onStartClicked() { emit startRequested(); }
void DebuggerPanel::onStopClicked() { emit stopRequested(); }
void DebuggerPanel::onPauseClicked() { emit pauseRequested(); }
void DebuggerPanel::onResumeClicked() { emit resumeRequested(); }
void DebuggerPanel::onStepIntoClicked() { emit stepIntoRequested(); }
void DebuggerPanel::onStepOverClicked() { emit stepOverRequested(); }
void DebuggerPanel::onStepOutClicked() { emit stepOutRequested(); }
void DebuggerPanel::onBreakpointItemChanged(QTreeWidgetItem* item, int column) {}

} // namespace GUI
} // namespace AutoCoder

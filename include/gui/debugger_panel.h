#ifndef AUTOCODER_DEBUGGER_PANEL_H
#define AUTOCODER_DEBUGGER_PANEL_H

#include <QWidget>
#include <QTreeWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <memory>

namespace AutoCoder {
namespace GUI {

class DebuggerPanel : public QWidget {
    Q_OBJECT

public:
    explicit DebuggerPanel(QWidget* parent = nullptr);
    ~DebuggerPanel();

    void updateCallStack(const QStringList& frames);
    void updateVariables(const QMap<QString, QString>& variables);
    void updateBreakpoints(const QStringList& breakpoints);

    void setDebuggerState(const QString& state);
    void highlightCurrentFrame(int frame_number);

signals:
    void startRequested();
    void stopRequested();
    void pauseRequested();
    void resumeRequested();
    void stepIntoRequested();
    void stepOverRequested();
    void stepOutRequested();
    void breakpointAdded(const QString& file, int line);
    void breakpointRemoved(int breakpoint_id);

private slots:
    void onStartClicked();
    void onStopClicked();
    void onPauseClicked();
    void onResumeClicked();
    void onStepIntoClicked();
    void onStepOverClicked();
    void onStepOutClicked();
    void onBreakpointItemChanged(QTreeWidgetItem* item, int column);

private:
    void setupUI();
    void updateControlButtons();

    QTreeWidget* call_stack_tree_;
    QTableWidget* variables_table_;
    QTreeWidget* breakpoints_tree_;

    QPushButton* start_button_;
    QPushButton* stop_button_;
    QPushButton* pause_button_;
    QPushButton* resume_button_;
    QPushButton* step_into_button_;
    QPushButton* step_over_button_;
    QPushButton* step_out_button_;

    QLabel* state_label_;
    QString current_state_;
};

} // namespace GUI
} // namespace AutoCoder

#endif // AUTOCODER_DEBUGGER_PANEL_H

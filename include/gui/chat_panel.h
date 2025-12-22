#ifndef AUTOCODER_CHAT_PANEL_H
#define AUTOCODER_CHAT_PANEL_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <memory>

namespace AutoCoder {
namespace GUI {

class ChatPanel : public QWidget {
    Q_OBJECT

public:
    explicit ChatPanel(QWidget* parent = nullptr);
    ~ChatPanel();

    void addMessage(const QString& role, const QString& message);
    void clearHistory();

    void setEnabled(bool enabled);

signals:
    void messageSent(const QString& message);
    void codeRequested(const QString& description);

private slots:
    void onSendButtonClicked();
    void onInputReturnPressed();
    void onGenerateCodeClicked();
    void onClearHistoryClicked();

private:
    void setupUI();
    void formatMessage(const QString& role, const QString& message);

    QTextEdit* chat_display_;
    QLineEdit* input_field_;
    QPushButton* send_button_;
    QPushButton* generate_code_button_;
    QPushButton* clear_button_;
    QVBoxLayout* layout_;

    bool is_waiting_for_response_;
};

} // namespace GUI
} // namespace AutoCoder

#endif // AUTOCODER_CHAT_PANEL_H

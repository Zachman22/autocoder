#include "gui/chat_panel.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

namespace AutoCoder {
namespace GUI {

ChatPanel::ChatPanel(QWidget* parent)
    : QWidget(parent)
    , is_waiting_for_response_(false) {
    setupUI();
}

ChatPanel::~ChatPanel() {}

void ChatPanel::setupUI() {
    layout_ = new QVBoxLayout(this);

    chat_display_ = new QTextEdit(this);
    chat_display_->setReadOnly(true);
    layout_->addWidget(chat_display_);

    input_field_ = new QLineEdit(this);
    input_field_->setPlaceholderText("Ask AI to generate code...");
    connect(input_field_, &QLineEdit::returnPressed, this, &ChatPanel::onInputReturnPressed);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    send_button_ = new QPushButton("Send", this);
    generate_code_button_ = new QPushButton("Generate Code", this);
    clear_button_ = new QPushButton("Clear", this);

    connect(send_button_, &QPushButton::clicked, this, &ChatPanel::onSendButtonClicked);
    connect(generate_code_button_, &QPushButton::clicked, this, &ChatPanel::onGenerateCodeClicked);
    connect(clear_button_, &QPushButton::clicked, this, &ChatPanel::onClearHistoryClicked);

    buttonLayout->addWidget(input_field_);
    buttonLayout->addWidget(send_button_);
    buttonLayout->addWidget(generate_code_button_);
    buttonLayout->addWidget(clear_button_);

    layout_->addLayout(buttonLayout);
    setLayout(layout_);
}

void ChatPanel::addMessage(const QString& role, const QString& message) {
    formatMessage(role, message);
}

void ChatPanel::formatMessage(const QString& role, const QString& message) {
    QString formatted = QString("<b>%1:</b> %2<br>").arg(role, message);
    chat_display_->append(formatted);
}

void ChatPanel::clearHistory() {
    chat_display_->clear();
}

void ChatPanel::onSendButtonClicked() {
    QString message = input_field_->text();
    if (!message.isEmpty()) {
        emit messageSent(message);
        input_field_->clear();
    }
}

void ChatPanel::onInputReturnPressed() {
    onSendButtonClicked();
}

void ChatPanel::onGenerateCodeClicked() {
    QString description = input_field_->text();
    if (!description.isEmpty()) {
        emit codeRequested(description);
        input_field_->clear();
    }
}

void ChatPanel::onClearHistoryClicked() {
    clearHistory();
}

} // namespace GUI
} // namespace AutoCoder

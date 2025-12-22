#include "gui/code_editor.h"
#include <QPainter>
#include <QTextBlock>

namespace AutoCoder {
namespace GUI {

CodeEditor::CodeEditor(QWidget* parent)
    : QPlainTextEdit(parent)
    , auto_indent_enabled_(true)
    , auto_complete_enabled_(true)
    , line_highlight_enabled_(true) {
    line_number_area_ = new LineNumberArea(this);
    setupEditor();

    connect(this, &QPlainTextEdit::blockCountChanged, this, &CodeEditor::updateLineNumberAreaWidth);
    connect(this, &QPlainTextEdit::updateRequest, this, &CodeEditor::updateLineNumberArea);
    connect(this, &QPlainTextEdit::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine);

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
}

CodeEditor::~CodeEditor() {}

void CodeEditor::setupEditor() {
    setTabStopDistance(40);
}

void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent* event) {
    QPainter painter(line_number_area_);
    painter.fillRect(event->rect(), Qt::lightGray);

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, line_number_area_->width(), fontMetrics().height(),
                           Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
        ++blockNumber;
    }
}

int CodeEditor::lineNumberAreaWidth() {
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;
    return space;
}

void CodeEditor::updateLineNumberAreaWidth(int newBlockCount) {
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void CodeEditor::updateLineNumberArea(const QRect& rect, int dy) {
    if (dy)
        line_number_area_->scroll(0, dy);
    else
        line_number_area_->update(0, rect.y(), line_number_area_->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void CodeEditor::resizeEvent(QResizeEvent* event) {
    QPlainTextEdit::resizeEvent(event);

    QRect cr = contentsRect();
    line_number_area_->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void CodeEditor::highlightCurrentLine() {
    if (!line_highlight_enabled_) return;

    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::yellow).lighter(160);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void CodeEditor::keyPressEvent(QKeyEvent* event) {
    QPlainTextEdit::keyPressEvent(event);

    if (auto_indent_enabled_ && event->key() == Qt::Key_Return) {
        autoIndent();
    }
}

void CodeEditor::autoIndent() {}
void CodeEditor::showAutoComplete() {}
void CodeEditor::setLanguage(const QString& language) { current_language_ = language; }
QString CodeEditor::getLanguage() const { return current_language_; }
void CodeEditor::setTheme(const QString& theme_name) {}
void CodeEditor::enableAutoIndent(bool enable) { auto_indent_enabled_ = enable; }
void CodeEditor::enableAutoComplete(bool enable) { auto_complete_enabled_ = enable; }
void CodeEditor::enableLineHighlight(bool enable) { line_highlight_enabled_ = enable; }
QString CodeEditor::getCurrentWord() { return ""; }
int CodeEditor::getCurrentLineNumber() { return textCursor().blockNumber() + 1; }

// LineNumberArea implementation
LineNumberArea::LineNumberArea(CodeEditor* editor) : QWidget(editor), code_editor_(editor) {}

QSize LineNumberArea::sizeHint() const {
    return QSize(code_editor_->lineNumberAreaWidth(), 0);
}

void LineNumberArea::paintEvent(QPaintEvent* event) {
    code_editor_->lineNumberAreaPaintEvent(event);
}

} // namespace GUI
} // namespace AutoCoder

#ifndef AUTOCODER_CODE_EDITOR_H
#define AUTOCODER_CODE_EDITOR_H

#include <QPlainTextEdit>
#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <memory>

namespace AutoCoder {
namespace GUI {

class LineNumberArea;
class SyntaxHighlighter;

class CodeEditor : public QPlainTextEdit {
    Q_OBJECT

public:
    explicit CodeEditor(QWidget* parent = nullptr);
    ~CodeEditor();

    void lineNumberAreaPaintEvent(QPaintEvent* event);
    int lineNumberAreaWidth();

    void setLanguage(const QString& language);
    QString getLanguage() const;

    void setTheme(const QString& theme_name);
    void enableAutoIndent(bool enable);
    void enableAutoComplete(bool enable);
    void enableLineHighlight(bool enable);

    QString getCurrentWord();
    int getCurrentLineNumber();

signals:
    void textModified();
    void languageChanged(const QString& language);

protected:
    void resizeEvent(QResizeEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect& rect, int dy);
    void autoIndent();
    void showAutoComplete();

private:
    void setupEditor();

    QWidget* line_number_area_;
    SyntaxHighlighter* syntax_highlighter_;
    QString current_language_;
    bool auto_indent_enabled_;
    bool auto_complete_enabled_;
    bool line_highlight_enabled_;
};

class LineNumberArea : public QWidget {
public:
    LineNumberArea(CodeEditor* editor);

    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    CodeEditor* code_editor_;
};

} // namespace GUI
} // namespace AutoCoder

#endif // AUTOCODER_CODE_EDITOR_H

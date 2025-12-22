#include <QApplication>
#include <QIcon>
#include <QStyleFactory>
#include "character_card/character_builder_window.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Set application information
    QApplication::setApplicationName("Character Card Builder");
    QApplication::setApplicationVersion("1.0.0");
    QApplication::setOrganizationName("Character Card Builder");
    QApplication::setOrganizationDomain("charactercardbuilder.app");

    // Set fusion style for consistent cross-platform appearance
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    // Set dark theme
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(106, 90, 205)); // SlateBlue
    darkPalette.setColor(QPalette::Highlight, QColor(106, 90, 205));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    QApplication::setPalette(darkPalette);

    // Apply global stylesheet for enhanced appearance
    app.setStyleSheet(R"(
        QToolTip {
            color: #ffffff;
            background-color: #2a82da;
            border: 1px solid white;
        }
        QScrollBar:vertical {
            background: #2a2a2a;
            width: 12px;
            margin: 0px;
        }
        QScrollBar::handle:vertical {
            background: #6a5acd;
            min-height: 20px;
            border-radius: 6px;
        }
        QScrollBar::handle:vertical:hover {
            background: #7a6add;
        }
        QScrollBar:horizontal {
            background: #2a2a2a;
            height: 12px;
            margin: 0px;
        }
        QScrollBar::handle:horizontal {
            background: #6a5acd;
            min-width: 20px;
            border-radius: 6px;
        }
        QScrollBar::handle:horizontal:hover {
            background: #7a6add;
        }
    )");

    // Create and show the main window
    AutoCoder::CharacterCard::CharacterBuilderWindow window;
    window.setWindowTitle("Character Card Builder - SillyTavern Card Creator");
    window.show();

    return app.exec();
}

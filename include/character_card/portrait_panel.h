#ifndef PORTRAIT_PANEL_H
#define PORTRAIT_PANEL_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <memory>

#include "character_card/card_data.h"

namespace AutoCoder {
namespace CharacterCard {

class PortraitPanel : public QWidget {
    Q_OBJECT

public:
    explicit PortraitPanel(std::shared_ptr<CharacterCardData> card, QWidget* parent = nullptr);
    ~PortraitPanel() override = default;

    void setCard(std::shared_ptr<CharacterCardData> card);
    void refresh();

signals:
    void modified();

private slots:
    void onLoadImage();
    void onClearImage();
    void onGenerateImage();

private:
    void setupUi();
    void loadFromCard();
    void displayImage();

    std::shared_ptr<CharacterCardData> currentCard;

    QLabel* imageLabel;
    QPushButton* loadButton;
    QPushButton* clearButton;
    QPushButton* generateButton;
};

} // namespace CharacterCard
} // namespace AutoCoder

#endif // PORTRAIT_PANEL_H

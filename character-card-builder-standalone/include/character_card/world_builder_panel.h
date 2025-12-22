#ifndef WORLD_BUILDER_PANEL_H
#define WORLD_BUILDER_PANEL_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QListWidget>
#include <QPushButton>
#include <memory>

#include "character_card/card_data.h"

namespace AutoCoder {
namespace CharacterCard {

class WorldBuilderPanel : public QWidget {
    Q_OBJECT

public:
    explicit WorldBuilderPanel(std::shared_ptr<CharacterCardData> card, QWidget* parent = nullptr);
    ~WorldBuilderPanel() override = default;

    void setCard(std::shared_ptr<CharacterCardData> card);
    void refresh();

signals:
    void modified();

private slots:
    void onWorldInfoChanged();
    void onAddLocation();
    void onAddFaction();
    void onAddNPC();

private:
    void setupUi();
    void loadFromCard();
    void saveToCard();

    std::shared_ptr<CharacterCardData> currentCard;

    QLineEdit* worldNameEdit;
    QTextEdit* worldDescriptionEdit;
    QLineEdit* settingEdit;
    QLineEdit* timePeriodEdit;
    QTextEdit* magicSystemEdit;
    QLineEdit* techLevelEdit;

    QListWidget* locationsList;
    QListWidget* factionsList;
    QListWidget* npcsList;
};

} // namespace CharacterCard
} // namespace AutoCoder

#endif // WORLD_BUILDER_PANEL_H

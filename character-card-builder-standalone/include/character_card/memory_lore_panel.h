#ifndef MEMORY_LORE_PANEL_H
#define MEMORY_LORE_PANEL_H

#include <QWidget>
#include <QTextEdit>
#include <QListWidget>
#include <QPushButton>
#include <memory>

#include "character_card/card_data.h"

namespace AutoCoder {
namespace CharacterCard {

class MemoryLorePanel : public QWidget {
    Q_OBJECT

public:
    explicit MemoryLorePanel(std::shared_ptr<CharacterCardData> card, QWidget* parent = nullptr);
    ~MemoryLorePanel() override = default;

    void setCard(std::shared_ptr<CharacterCardData> card);
    void refresh();
    void setSimpleMode(bool simple);

signals:
    void modified();

private slots:
    void onMemoryChanged();
    void onAddNeverDo();
    void onAddHardLimit();
    void onAddSoftLimit();
    void onRemoveNeverDo();
    void onRemoveHardLimit();
    void onRemoveSoftLimit();

private:
    void setupUi();
    void loadFromCard();
    void saveToCard();

    std::shared_ptr<CharacterCardData> currentCard;
    bool simpleMode;

    QTextEdit* persistentMemoryEdit;
    QTextEdit* relationshipMemoryEdit;
    QTextEdit* worldLoreEdit;
    QTextEdit* characterHistoryEdit;
    QTextEdit* emotionalTriggersEdit;

    QListWidget* neverDoList;
    QListWidget* hardLimitsList;
    QListWidget* softLimitsList;

    QPushButton* addNeverDoButton;
    QPushButton* addHardLimitButton;
    QPushButton* addSoftLimitButton;
};

} // namespace CharacterCard
} // namespace AutoCoder

#endif // MEMORY_LORE_PANEL_H

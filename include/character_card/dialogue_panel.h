#ifndef DIALOGUE_PANEL_H
#define DIALOGUE_PANEL_H

#include <QWidget>
#include <QListWidget>
#include <QTextEdit>
#include <QPushButton>
#include <memory>

#include "character_card/card_data.h"

namespace AutoCoder {
namespace CharacterCard {

class DialoguePanel : public QWidget {
    Q_OBJECT

public:
    explicit DialoguePanel(std::shared_ptr<CharacterCardData> card, QWidget* parent = nullptr);
    ~DialoguePanel() override = default;

    void setCard(std::shared_ptr<CharacterCardData> card);
    void refresh();

signals:
    void modified();

private slots:
    void onAddDialogue();
    void onRemoveDialogue();
    void onGenerateDialogue();
    void onDialogueSelected(int index);
    void onUserMessageChanged();
    void onCharResponseChanged();

private:
    void setupUi();
    void loadFromCard();
    void saveToCard();
    void updateDialogueList();

    std::shared_ptr<CharacterCardData> currentCard;

    QListWidget* dialogueList;
    QTextEdit* userMessageEdit;
    QTextEdit* charResponseEdit;
    QPushButton* addButton;
    QPushButton* removeButton;
    QPushButton* generateButton;

    int currentDialogueIndex;
};

} // namespace CharacterCard
} // namespace AutoCoder

#endif // DIALOGUE_PANEL_H

#include "character_card/dialogue_panel.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

namespace AutoCoder {
namespace CharacterCard {

DialoguePanel::DialoguePanel(std::shared_ptr<CharacterCardData> card, QWidget* parent)
    : QWidget(parent), currentCard(card), currentDialogueIndex(-1) {
    setupUi();
    loadFromCard();
}

void DialoguePanel::setupUi() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    
    dialogueList = new QListWidget(this);
    mainLayout->addWidget(new QLabel("Example Dialogues:"));
    mainLayout->addWidget(dialogueList);
    
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    addButton = new QPushButton("Add", this);
    removeButton = new QPushButton("Remove", this);
    generateButton = new QPushButton("Generate", this);
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(removeButton);
    buttonLayout->addWidget(generateButton);
    mainLayout->addLayout(buttonLayout);
    
    connect(addButton, &QPushButton::clicked, this, &DialoguePanel::onAddDialogue);
    connect(removeButton, &QPushButton::clicked, this, &DialoguePanel::onRemoveDialogue);
    connect(generateButton, &QPushButton::clicked, this, &DialoguePanel::onGenerateDialogue);
}

void DialoguePanel::setCard(std::shared_ptr<CharacterCardData> card) {
    currentCard = card;
    loadFromCard();
}

void DialoguePanel::refresh() {
    loadFromCard();
}

void DialoguePanel::loadFromCard() {
    if (!currentCard) return;
    updateDialogueList();
}

void DialoguePanel::saveToCard() {}

void DialoguePanel::updateDialogueList() {
    dialogueList->clear();
    if (currentCard) {
        for (const auto& dialogue : currentCard->example_dialogues) {
            dialogueList->addItem(QString::fromStdString(dialogue.user_message.substr(0, 50) + "..."));
        }
    }
}

void DialoguePanel::onAddDialogue() { emit modified(); }
void DialoguePanel::onRemoveDialogue() { emit modified(); }
void DialoguePanel::onGenerateDialogue() { emit modified(); }
void DialoguePanel::onDialogueSelected(int) {}
void DialoguePanel::onUserMessageChanged() { emit modified(); }
void DialoguePanel::onCharResponseChanged() { emit modified(); }

} // namespace CharacterCard
} // namespace AutoCoder

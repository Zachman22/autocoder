#include "character_card/memory_lore_panel.h"
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>

namespace AutoCoder {
namespace CharacterCard {

MemoryLorePanel::MemoryLorePanel(std::shared_ptr<CharacterCardData> card, QWidget* parent)
    : QWidget(parent), currentCard(card), simpleMode(true) {
    setupUi();
    loadFromCard();
}

void MemoryLorePanel::setupUi() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    
    QGroupBox* memoryGroup = new QGroupBox("Memory & Lore", this);
    QVBoxLayout* memoryLayout = new QVBoxLayout(memoryGroup);
    
    memoryLayout->addWidget(new QLabel("Persistent Memory:"));
    persistentMemoryEdit = new QTextEdit(this);
    memoryLayout->addWidget(persistentMemoryEdit);
    
    memoryLayout->addWidget(new QLabel("Character History:"));
    characterHistoryEdit = new QTextEdit(this);
    memoryLayout->addWidget(characterHistoryEdit);
    
    mainLayout->addWidget(memoryGroup);
    mainLayout->addStretch();
}

void MemoryLorePanel::setCard(std::shared_ptr<CharacterCardData> card) {
    currentCard = card;
    loadFromCard();
}

void MemoryLorePanel::refresh() {
    loadFromCard();
}

void MemoryLorePanel::setSimpleMode(bool simple) {
    simpleMode = simple;
}

void MemoryLorePanel::loadFromCard() {
    if (!currentCard) return;
    persistentMemoryEdit->setPlainText(QString::fromStdString(currentCard->memory_lore.persistent_memory));
    characterHistoryEdit->setPlainText(QString::fromStdString(currentCard->memory_lore.character_history));
}

void MemoryLorePanel::saveToCard() {
    if (!currentCard) return;
    currentCard->memory_lore.persistent_memory = persistentMemoryEdit->toPlainText().toStdString();
    currentCard->memory_lore.character_history = characterHistoryEdit->toPlainText().toStdString();
}

void MemoryLorePanel::onMemoryChanged() {
    saveToCard();
    emit modified();
}

void MemoryLorePanel::onAddNeverDo() { emit modified(); }
void MemoryLorePanel::onAddHardLimit() { emit modified(); }
void MemoryLorePanel::onAddSoftLimit() { emit modified(); }
void MemoryLorePanel::onRemoveNeverDo() { emit modified(); }
void MemoryLorePanel::onRemoveHardLimit() { emit modified(); }
void MemoryLorePanel::onRemoveSoftLimit() { emit modified(); }

} // namespace CharacterCard
} // namespace AutoCoder

#include "character_card/world_builder_panel.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QGroupBox>

namespace AutoCoder {
namespace CharacterCard {

WorldBuilderPanel::WorldBuilderPanel(std::shared_ptr<CharacterCardData> card, QWidget* parent)
    : QWidget(parent), currentCard(card) {
    setupUi();
    loadFromCard();
}

void WorldBuilderPanel::setupUi() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    
    QGroupBox* group = new QGroupBox("World Information", this);
    QFormLayout* form = new QFormLayout(group);
    
    worldNameEdit = new QLineEdit(this);
    form->addRow("World Name:", worldNameEdit);
    
    worldDescriptionEdit = new QTextEdit(this);
    worldDescriptionEdit->setMaximumHeight(100);
    form->addRow("Description:", worldDescriptionEdit);
    
    settingEdit = new QLineEdit(this);
    form->addRow("Setting:", settingEdit);
    
    mainLayout->addWidget(group);
    mainLayout->addStretch();
}

void WorldBuilderPanel::setCard(std::shared_ptr<CharacterCardData> card) {
    currentCard = card;
    loadFromCard();
}

void WorldBuilderPanel::refresh() {
    loadFromCard();
}

void WorldBuilderPanel::loadFromCard() {
    if (!currentCard || !currentCard->world_info) return;
    worldNameEdit->setText(QString::fromStdString(currentCard->world_info->name));
    worldDescriptionEdit->setPlainText(QString::fromStdString(currentCard->world_info->description));
    settingEdit->setText(QString::fromStdString(currentCard->world_info->setting));
}

void WorldBuilderPanel::saveToCard() {
    if (!currentCard) return;
    if (!currentCard->world_info) {
        currentCard->world_info = std::make_shared<WorldInfo>();
    }
    currentCard->world_info->name = worldNameEdit->text().toStdString();
    currentCard->world_info->description = worldDescriptionEdit->toPlainText().toStdString();
    currentCard->world_info->setting = settingEdit->text().toStdString();
}

void WorldBuilderPanel::onWorldInfoChanged() { saveToCard(); emit modified(); }
void WorldBuilderPanel::onAddLocation() { emit modified(); }
void WorldBuilderPanel::onAddFaction() { emit modified(); }
void WorldBuilderPanel::onAddNPC() { emit modified(); }

} // namespace CharacterCard
} // namespace AutoCoder

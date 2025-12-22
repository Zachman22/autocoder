#include "character_card/basic_info_panel.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>

namespace AutoCoder {
namespace CharacterCard {

BasicInfoPanel::BasicInfoPanel(std::shared_ptr<CharacterCardData> card, QWidget* parent)
    : QWidget(parent), currentCard(card), simpleMode(true) {
    setupUi();
    loadFromCard();
}

void BasicInfoPanel::setupUi() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Basic info group
    QGroupBox* basicGroup = new QGroupBox("Basic Information", this);
    QFormLayout* basicForm = new QFormLayout(basicGroup);

    nameEdit = new QLineEdit(this);
    connect(nameEdit, &QLineEdit::textChanged, this, &BasicInfoPanel::onNameChanged);
    basicForm->addRow("Character Name*:", nameEdit);

    nicknameEdit = new QLineEdit(this);
    basicForm->addRow("Nickname:", nicknameEdit);

    pronounsEdit = new QLineEdit(this);
    pronounsEdit->setPlaceholderText("e.g., she/her, he/him, they/them");
    basicForm->addRow("Pronouns:", pronounsEdit);

    povCombo = new QComboBox(this);
    povCombo->addItem("First Person");
    povCombo->addItem("Second Person");
    povCombo->addItem("Third Person");
    basicForm->addRow("POV Style:", povCombo);

    speakingStyleCombo = new QComboBox(this);
    speakingStyleCombo->addItems({"Formal", "Casual", "Shy", "Sarcastic", "Teasing", "Dominant", "Submissive", "Custom"});
    basicForm->addRow("Speaking Style:", speakingStyleCombo);

    mainLayout->addWidget(basicGroup);

    // Description group
    QGroupBox* descGroup = new QGroupBox("Description & Personality", this);
    QVBoxLayout* descLayout = new QVBoxLayout(descGroup);

    descLayout->addWidget(new QLabel("Description:"));
    descriptionEdit = new QTextEdit(this);
    descriptionEdit->setPlaceholderText("Physical appearance, background, and general description...");
    connect(descriptionEdit, &QTextEdit::textChanged, this, &BasicInfoPanel::onDescriptionChanged);
    descLayout->addWidget(descriptionEdit);

    descLayout->addWidget(new QLabel("Personality:"));
    personalityEdit = new QTextEdit(this);
    personalityEdit->setPlaceholderText("Character traits, behavior, and personality...");
    connect(personalityEdit, &QTextEdit::textChanged, this, &BasicInfoPanel::onPersonalityChanged);
    descLayout->addWidget(personalityEdit);

    mainLayout->addWidget(descGroup);

    // Scenario group
    QGroupBox* scenarioGroup = new QGroupBox("Scenario & First Message", this);
    QVBoxLayout* scenarioLayout = new QVBoxLayout(scenarioGroup);

    scenarioLayout->addWidget(new QLabel("Scenario:"));
    scenarioEdit = new QTextEdit(this);
    scenarioEdit->setPlaceholderText("The setting and context for interactions...");
    connect(scenarioEdit, &QTextEdit::textChanged, this, &BasicInfoPanel::onScenarioChanged);
    scenarioLayout->addWidget(scenarioEdit);

    scenarioLayout->addWidget(new QLabel("First Message:"));
    firstMessageEdit = new QTextEdit(this);
    firstMessageEdit->setPlaceholderText("The character's greeting message...");
    connect(firstMessageEdit, &QTextEdit::textChanged, this, &BasicInfoPanel::onFirstMessageChanged);
    scenarioLayout->addWidget(firstMessageEdit);

    mainLayout->addWidget(scenarioGroup);

    // Author
    QFormLayout* authorForm = new QFormLayout();
    authorEdit = new QLineEdit(this);
    authorForm->addRow("Author:", authorEdit);
    mainLayout->addLayout(authorForm);

    mainLayout->addStretch();
}

void BasicInfoPanel::setCard(std::shared_ptr<CharacterCardData> card) {
    currentCard = card;
    loadFromCard();
}

void BasicInfoPanel::refresh() {
    loadFromCard();
}

void BasicInfoPanel::setSimpleMode(bool simple) {
    simpleMode = simple;
}

void BasicInfoPanel::loadFromCard() {
    if (!currentCard) return;

    nameEdit->setText(QString::fromStdString(currentCard->name));
    nicknameEdit->setText(QString::fromStdString(currentCard->nickname));
    pronounsEdit->setText(QString::fromStdString(currentCard->pronouns));
    povCombo->setCurrentIndex(static_cast<int>(currentCard->pov_style));
    speakingStyleCombo->setCurrentIndex(static_cast<int>(currentCard->speaking_style));
    descriptionEdit->setPlainText(QString::fromStdString(currentCard->description));
    personalityEdit->setPlainText(QString::fromStdString(currentCard->personality));
    scenarioEdit->setPlainText(QString::fromStdString(currentCard->scenario));
    firstMessageEdit->setPlainText(QString::fromStdString(currentCard->first_message));
    authorEdit->setText(QString::fromStdString(currentCard->author));
}

void BasicInfoPanel::saveToCard() {
    if (!currentCard) return;

    currentCard->name = nameEdit->text().toStdString();
    currentCard->nickname = nicknameEdit->text().toStdString();
    currentCard->pronouns = pronounsEdit->text().toStdString();
    currentCard->pov_style = static_cast<POVStyle>(povCombo->currentIndex());
    currentCard->speaking_style = static_cast<SpeakingStyle>(speakingStyleCombo->currentIndex());
    currentCard->description = descriptionEdit->toPlainText().toStdString();
    currentCard->personality = personalityEdit->toPlainText().toStdString();
    currentCard->scenario = scenarioEdit->toPlainText().toStdString();
    currentCard->first_message = firstMessageEdit->toPlainText().toStdString();
    currentCard->author = authorEdit->text().toStdString();
}

void BasicInfoPanel::onNameChanged() {
    saveToCard();
    emit modified();
}

void BasicInfoPanel::onDescriptionChanged() {
    saveToCard();
    emit modified();
}

void BasicInfoPanel::onPersonalityChanged() {
    saveToCard();
    emit modified();
}

void BasicInfoPanel::onScenarioChanged() {
    saveToCard();
    emit modified();
}

void BasicInfoPanel::onFirstMessageChanged() {
    saveToCard();
    emit modified();
}

} // namespace CharacterCard
} // namespace AutoCoder

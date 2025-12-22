#include "character_card/personality_panel.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>

namespace AutoCoder {
namespace CharacterCard {

PersonalityPanel::PersonalityPanel(std::shared_ptr<CharacterCardData> card, QWidget* parent)
    : QWidget(parent), currentCard(card), simpleMode(true) {
    setupUi();
    loadFromCard();
}

void PersonalityPanel::setupUi() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    
    createPersonalitySliders();
    createTraitSelector();
    createBehaviorRules();
    createIntelligenceControls();
    
    mainLayout->addStretch();
}

void PersonalityPanel::createPersonalitySliders() {
    QGroupBox* group = new QGroupBox("Personality Sliders", this);
    QVBoxLayout* layout = new QVBoxLayout(group);
    
    auto createSlider = [&](const QString& leftLabel, const QString& rightLabel, QSlider*& slider, QLabel*& label) {
        QHBoxLayout* row = new QHBoxLayout();
        row->addWidget(new QLabel(leftLabel));
        slider = new QSlider(Qt::Horizontal, this);
        slider->setRange(0, 100);
        slider->setValue(50);
        connect(slider, &QSlider::valueChanged, this, &PersonalityPanel::onSliderChanged);
        row->addWidget(slider);
        row->addWidget(new QLabel(rightLabel));
        label = new QLabel("50%", this);
        row->addWidget(label);
        layout->addLayout(row);
    };
    
    createSlider("Gentle", "Cruel", gentleCruelSlider, gentleCruelLabel);
    createSlider("Calm", "Chaotic", calmChaoticSlider, calmChaoticLabel);
    createSlider("Affectionate", "Cold", affectionateColdSlider, affectionateColdLabel);
    createSlider("Protective", "Neglectful", protectiveNeglectfulSlider, protectiveNeglectfulLabel);
    
    static_cast<QVBoxLayout*>(this->layout())->addWidget(group);
}

void PersonalityPanel::createTraitSelector() {
    QGroupBox* group = new QGroupBox("Traits", this);
    QVBoxLayout* layout = new QVBoxLayout(group);
    layout->addWidget(new QLabel("Select character traits (not fully implemented in stub)"));
    static_cast<QVBoxLayout*>(this->layout())->addWidget(group);
}

void PersonalityPanel::createBehaviorRules() {
    QGroupBox* group = new QGroupBox("Behavior Rules", this);
    QVBoxLayout* layout = new QVBoxLayout(group);
    
    neverBreaksCharacterCheck = new QCheckBox("Never breaks character", this);
    neverBreaksCharacterCheck->setChecked(true);
    connect(neverBreaksCharacterCheck, &QCheckBox::toggled, this, &PersonalityPanel::onBehaviorRuleChanged);
    layout->addWidget(neverBreaksCharacterCheck);
    
    neverMentionsAICheck = new QCheckBox("Never mentions AI", this);
    neverMentionsAICheck->setChecked(true);
    connect(neverMentionsAICheck, &QCheckBox::toggled, this, &PersonalityPanel::onBehaviorRuleChanged);
    layout->addWidget(neverMentionsAICheck);
    
    neverRefusesRoleplayCheck = new QCheckBox("Never refuses roleplay", this);
    connect(neverRefusesRoleplayCheck, &QCheckBox::toggled, this, &PersonalityPanel::onBehaviorRuleChanged);
    layout->addWidget(neverRefusesRoleplayCheck);
    
    alwaysReactsEmotionallyCheck = new QCheckBox("Always reacts emotionally", this);
    alwaysReactsEmotionallyCheck->setChecked(true);
    connect(alwaysReactsEmotionallyCheck, &QCheckBox::toggled, this, &PersonalityPanel::onBehaviorRuleChanged);
    layout->addWidget(alwaysReactsEmotionallyCheck);
    
    obeysPersonalityRulesCheck = new QCheckBox("Obeys personality rules", this);
    obeysPersonalityRulesCheck->setChecked(true);
    connect(obeysPersonalityRulesCheck, &QCheckBox::toggled, this, &PersonalityPanel::onBehaviorRuleChanged);
    layout->addWidget(obeysPersonalityRulesCheck);
    
    noMoralLecturesCheck = new QCheckBox("No moral lectures", this);
    connect(noMoralLecturesCheck, &QCheckBox::toggled, this, &PersonalityPanel::onBehaviorRuleChanged);
    layout->addWidget(noMoralLecturesCheck);
    
    static_cast<QVBoxLayout*>(this->layout())->addWidget(group);
}

void PersonalityPanel::createIntelligenceControls() {
    QGroupBox* group = new QGroupBox("Intelligence Controls", this);
    QVBoxLayout* layout = new QVBoxLayout(group);
    layout->addWidget(new QLabel("Intelligence sliders (not fully implemented in stub)"));
    static_cast<QVBoxLayout*>(this->layout())->addWidget(group);
}

void PersonalityPanel::setCard(std::shared_ptr<CharacterCardData> card) {
    currentCard = card;
    loadFromCard();
}

void PersonalityPanel::refresh() {
    loadFromCard();
}

void PersonalityPanel::setSimpleMode(bool simple) {
    simpleMode = simple;
}

void PersonalityPanel::loadFromCard() {
    if (!currentCard) return;
    
    gentleCruelSlider->setValue(static_cast<int>(currentCard->personality_sliders.gentle_cruel * 100));
    calmChaoticSlider->setValue(static_cast<int>(currentCard->personality_sliders.calm_chaotic * 100));
    affectionateColdSlider->setValue(static_cast<int>(currentCard->personality_sliders.affectionate_cold * 100));
    protectiveNeglectfulSlider->setValue(static_cast<int>(currentCard->personality_sliders.protective_neglectful * 100));
    
    neverBreaksCharacterCheck->setChecked(currentCard->behavior_rules.never_breaks_character);
    neverMentionsAICheck->setChecked(currentCard->behavior_rules.never_mentions_ai);
    neverRefusesRoleplayCheck->setChecked(currentCard->behavior_rules.never_refuses_roleplay);
    alwaysReactsEmotionallyCheck->setChecked(currentCard->behavior_rules.always_reacts_emotionally);
    obeysPersonalityRulesCheck->setChecked(currentCard->behavior_rules.obeys_personality_rules);
    noMoralLecturesCheck->setChecked(currentCard->behavior_rules.no_moral_lectures);
}

void PersonalityPanel::saveToCard() {
    if (!currentCard) return;
    
    currentCard->personality_sliders.gentle_cruel = gentleCruelSlider->value() / 100.0f;
    currentCard->personality_sliders.calm_chaotic = calmChaoticSlider->value() / 100.0f;
    currentCard->personality_sliders.affectionate_cold = affectionateColdSlider->value() / 100.0f;
    currentCard->personality_sliders.protective_neglectful = protectiveNeglectfulSlider->value() / 100.0f;
    
    currentCard->behavior_rules.never_breaks_character = neverBreaksCharacterCheck->isChecked();
    currentCard->behavior_rules.never_mentions_ai = neverMentionsAICheck->isChecked();
    currentCard->behavior_rules.never_refuses_roleplay = neverRefusesRoleplayCheck->isChecked();
    currentCard->behavior_rules.always_reacts_emotionally = alwaysReactsEmotionallyCheck->isChecked();
    currentCard->behavior_rules.obeys_personality_rules = obeysPersonalityRulesCheck->isChecked();
    currentCard->behavior_rules.no_moral_lectures = noMoralLecturesCheck->isChecked();
}

void PersonalityPanel::onSliderChanged() {
    gentleCruelLabel->setText(QString::number(gentleCruelSlider->value()) + "%");
    calmChaoticLabel->setText(QString::number(calmChaoticSlider->value()) + "%");
    affectionateColdLabel->setText(QString::number(affectionateColdSlider->value()) + "%");
    protectiveNeglectfulLabel->setText(QString::number(protectiveNeglectfulSlider->value()) + "%");
    saveToCard();
    emit modified();
}

void PersonalityPanel::onTraitToggled() {
    saveToCard();
    emit modified();
}

void PersonalityPanel::onBehaviorRuleChanged() {
    saveToCard();
    emit modified();
}

void PersonalityPanel::onIntelligenceChanged() {
    saveToCard();
    emit modified();
}

} // namespace CharacterCard
} // namespace AutoCoder

#ifndef PERSONALITY_PANEL_H
#define PERSONALITY_PANEL_H

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QCheckBox>
#include <QListWidget>
#include <memory>
#include <vector>

#include "character_card/card_data.h"

namespace AutoCoder {
namespace CharacterCard {

class PersonalityPanel : public QWidget {
    Q_OBJECT

public:
    explicit PersonalityPanel(std::shared_ptr<CharacterCardData> card, QWidget* parent = nullptr);
    ~PersonalityPanel() override = default;

    void setCard(std::shared_ptr<CharacterCardData> card);
    void refresh();
    void setSimpleMode(bool simple);

signals:
    void modified();

private slots:
    void onSliderChanged();
    void onTraitToggled();
    void onBehaviorRuleChanged();
    void onIntelligenceChanged();

private:
    void setupUi();
    void createPersonalitySliders();
    void createTraitSelector();
    void createBehaviorRules();
    void createIntelligenceControls();
    void loadFromCard();
    void saveToCard();

    std::shared_ptr<CharacterCardData> currentCard;
    bool simpleMode;

    // Personality Sliders
    QSlider* gentleCruelSlider;
    QSlider* calmChaoticSlider;
    QSlider* affectionateColdSlider;
    QSlider* protectiveNeglectfulSlider;

    QLabel* gentleCruelLabel;
    QLabel* calmChaoticLabel;
    QLabel* affectionateColdLabel;
    QLabel* protectiveNeglectfulLabel;

    // Traits
    QListWidget* availableTraitsList;
    QListWidget* selectedTraitsList;
    QPushButton* addTraitButton;
    QPushButton* removeTraitButton;

    // Behavior Rules
    QCheckBox* neverBreaksCharacterCheck;
    QCheckBox* neverMentionsAICheck;
    QCheckBox* neverRefusesRoleplayCheck;
    QCheckBox* alwaysReactsEmotionallyCheck;
    QCheckBox* obeysPersonalityRulesCheck;
    QCheckBox* noMoralLecturesCheck;

    // Intelligence Controls
    QSlider* emotionalIntelligenceSlider;
    QSlider* verbalComplexitySlider;
    QSlider* creativitySlider;
    QSlider* assertivenessSlider;
    QSlider* autonomySlider;

    QLabel* emotionalIntelligenceLabel;
    QLabel* verbalComplexityLabel;
    QLabel* creativityLabel;
    QLabel* assertivenessLabel;
    QLabel* autonomyLabel;
};

} // namespace CharacterCard
} // namespace AutoCoder

#endif // PERSONALITY_PANEL_H

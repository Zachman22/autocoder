#ifndef BASIC_INFO_PANEL_H
#define BASIC_INFO_PANEL_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QPushButton>
#include <memory>

#include "character_card/card_data.h"

namespace AutoCoder {
namespace CharacterCard {

class BasicInfoPanel : public QWidget {
    Q_OBJECT

public:
    explicit BasicInfoPanel(std::shared_ptr<CharacterCardData> card, QWidget* parent = nullptr);
    ~BasicInfoPanel() override = default;

    void setCard(std::shared_ptr<CharacterCardData> card);
    void refresh();
    void setSimpleMode(bool simple);

signals:
    void modified();

private slots:
    void onNameChanged();
    void onDescriptionChanged();
    void onPersonalityChanged();
    void onScenarioChanged();
    void onFirstMessageChanged();

private:
    void setupUi();
    void loadFromCard();
    void saveToCard();

    std::shared_ptr<CharacterCardData> currentCard;
    bool simpleMode;

    // UI Components
    QLineEdit* nameEdit;
    QLineEdit* nicknameEdit;
    QLineEdit* pronounsEdit;
    QComboBox* povCombo;
    QComboBox* speakingStyleCombo;
    QTextEdit* descriptionEdit;
    QTextEdit* personalityEdit;
    QTextEdit* scenarioEdit;
    QTextEdit* firstMessageEdit;
    QLineEdit* authorEdit;
};

} // namespace CharacterCard
} // namespace AutoCoder

#endif // BASIC_INFO_PANEL_H

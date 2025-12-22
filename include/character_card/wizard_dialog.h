#ifndef WIZARD_DIALOG_H
#define WIZARD_DIALOG_H

#include <QWizard>
#include <QWizardPage>
#include <memory>

#include "character_card/card_data.h"

namespace AutoCoder {
namespace CharacterCard {

class WizardDialog : public QWizard {
    Q_OBJECT

public:
    explicit WizardDialog(std::shared_ptr<CharacterCardData> card, QWidget* parent = nullptr);
    ~WizardDialog() override = default;

private:
    void setupPages();

    std::shared_ptr<CharacterCardData> currentCard;
};

// Wizard pages
class WizardIntroPage : public QWizardPage {
    Q_OBJECT
public:
    explicit WizardIntroPage(QWidget* parent = nullptr);
};

class WizardBasicInfoPage : public QWizardPage {
    Q_OBJECT
public:
    explicit WizardBasicInfoPage(std::shared_ptr<CharacterCardData> card, QWidget* parent = nullptr);

private:
    void setupUi();
    std::shared_ptr<CharacterCardData> currentCard;
};

class WizardPersonalityPage : public QWizardPage {
    Q_OBJECT
public:
    explicit WizardPersonalityPage(std::shared_ptr<CharacterCardData> card, QWidget* parent = nullptr);

private:
    void setupUi();
    std::shared_ptr<CharacterCardData> currentCard;
};

class WizardFinishPage : public QWizardPage {
    Q_OBJECT
public:
    explicit WizardFinishPage(std::shared_ptr<CharacterCardData> card, QWidget* parent = nullptr);

private:
    void setupUi();
    std::shared_ptr<CharacterCardData> currentCard;
};

} // namespace CharacterCard
} // namespace AutoCoder

#endif // WIZARD_DIALOG_H

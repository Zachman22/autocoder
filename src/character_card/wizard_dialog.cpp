#include "character_card/wizard_dialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>

namespace AutoCoder {
namespace CharacterCard {

WizardDialog::WizardDialog(std::shared_ptr<CharacterCardData> card, QWidget* parent)
    : QWizard(parent), currentCard(card) {
    setWindowTitle("Character Creation Wizard");
    setupPages();
}

void WizardDialog::setupPages() {
    addPage(new WizardIntroPage(this));
    addPage(new WizardBasicInfoPage(currentCard, this));
    addPage(new WizardPersonalityPage(currentCard, this));
    addPage(new WizardFinishPage(currentCard, this));
}

// WizardIntroPage
WizardIntroPage::WizardIntroPage(QWidget* parent) : QWizardPage(parent) {
    setTitle("Welcome to Character Builder");
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("This wizard will guide you through creating a character card."));
}

// WizardBasicInfoPage
WizardBasicInfoPage::WizardBasicInfoPage(std::shared_ptr<CharacterCardData> card, QWidget* parent)
    : QWizardPage(parent), currentCard(card) {
    setupUi();
}

void WizardBasicInfoPage::setupUi() {
    setTitle("Basic Information");
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Enter basic character information:"));
    QLineEdit* nameEdit = new QLineEdit(this);
    layout->addWidget(new QLabel("Character Name:"));
    layout->addWidget(nameEdit);
}

// WizardPersonalityPage
WizardPersonalityPage::WizardPersonalityPage(std::shared_ptr<CharacterCardData> card, QWidget* parent)
    : QWizardPage(parent), currentCard(card) {
    setupUi();
}

void WizardPersonalityPage::setupUi() {
    setTitle("Personality");
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Configure personality traits (simplified in stub)"));
}

// WizardFinishPage
WizardFinishPage::WizardFinishPage(std::shared_ptr<CharacterCardData> card, QWidget* parent)
    : QWizardPage(parent), currentCard(card) {
    setupUi();
}

void WizardFinishPage::setupUi() {
    setTitle("Complete");
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Your character card has been created!"));
}

} // namespace CharacterCard
} // namespace AutoCoder

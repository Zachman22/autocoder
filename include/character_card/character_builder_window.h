#ifndef CHARACTER_BUILDER_WINDOW_H
#define CHARACTER_BUILDER_WINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel>
#include <memory>

#include "character_card/card_data.h"
#include "character_card/card_validator.h"

namespace AutoCoder {
namespace CharacterCard {

// Forward declarations
class BasicInfoPanel;
class PersonalityPanel;
class MemoryLorePanel;
class DialoguePanel;
class WorldBuilderPanel;
class PortraitPanel;
class ExportDialog;

class CharacterBuilderWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit CharacterBuilderWindow(QWidget* parent = nullptr);
    ~CharacterBuilderWindow() override;

    // Card management
    void newCard();
    void loadCard(const std::string& filepath);
    void saveCard(const std::string& filepath);
    void importCard(const std::string& filepath);

    // Get current card
    std::shared_ptr<CharacterCardData> getCurrentCard() const { return currentCard; }

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void onNewCard();
    void onOpenCard();
    void onSaveCard();
    void onSaveCardAs();
    void onImportCard();
    void onExportCard();
    void onValidateCard();
    void onCardModified();
    void onSwitchMode();
    void onShowWizard();
    void onLoadPreset();
    void onSaveAsPreset();
    void onImportKinks();

private:
    void setupUi();
    void setupMenuBar();
    void setupToolBar();
    void setupStatusBar();
    void createPanels();
    void connectSignals();

    void updateTitle();
    void updateValidationStatus();
    bool promptSaveIfModified();

    // UI Components
    QTabWidget* tabWidget;
    QToolBar* toolBar;
    QStatusBar* statusBar;
    QLabel* validationStatusLabel;

    // Panels
    BasicInfoPanel* basicInfoPanel;
    PersonalityPanel* personalityPanel;
    MemoryLorePanel* memoryLorePanel;
    DialoguePanel* dialoguePanel;
    WorldBuilderPanel* worldBuilderPanel;
    PortraitPanel* portraitPanel;

    // Data
    std::shared_ptr<CharacterCardData> currentCard;
    CardValidator validator;
    std::string currentFilepath;
    bool isModified;
    bool isSimpleMode; // Simple vs Advanced mode

    // Actions
    QAction* newAction;
    QAction* openAction;
    QAction* saveAction;
    QAction* saveAsAction;
    QAction* importAction;
    QAction* exportAction;
    QAction* validateAction;
    QAction* wizardAction;
    QAction* modeToggleAction;
    QAction* loadPresetAction;
    QAction* savePresetAction;
    QAction* importKinksAction;
};

} // namespace CharacterCard
} // namespace AutoCoder

#endif // CHARACTER_BUILDER_WINDOW_H

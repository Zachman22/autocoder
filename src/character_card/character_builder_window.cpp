#include "character_card/character_builder_window.h"
#include "character_card/basic_info_panel.h"
#include "character_card/personality_panel.h"
#include "character_card/memory_lore_panel.h"
#include "character_card/dialogue_panel.h"
#include "character_card/world_builder_panel.h"
#include "character_card/portrait_panel.h"
#include "character_card/export_dialog.h"
#include "character_card/wizard_dialog.h"
#include "character_card/preset_manager.h"
#include "character_card/card_importer.h"
#include "character_card/web_scraper.h"

#include <QMenuBar>
#include <QToolBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QCloseEvent>
#include <QProgressDialog>

namespace AutoCoder {
namespace CharacterCard {

CharacterBuilderWindow::CharacterBuilderWindow(QWidget* parent)
    : QMainWindow(parent),
      isModified(false),
      isSimpleMode(true) {

    currentCard = std::make_shared<CharacterCardData>();

    setupUi();
    setupMenuBar();
    setupToolBar();
    setupStatusBar();
    createPanels();
    connectSignals();

    updateTitle();
    updateValidationStatus();

    resize(1200, 800);
}

CharacterBuilderWindow::~CharacterBuilderWindow() {
}

void CharacterBuilderWindow::setupUi() {
    setWindowTitle("Character Card Builder");

    // Create central widget and tab widget
    tabWidget = new QTabWidget(this);
    tabWidget->setTabPosition(QTabWidget::West);
    setCentralWidget(tabWidget);

    // Apply elegant styling
    setStyleSheet(R"(
        QMainWindow {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                       stop:0 #2c2c2c, stop:1 #1e1e1e);
        }
        QTabWidget::pane {
            border: 1px solid #444;
            background: #2a2a2a;
            border-radius: 5px;
        }
        QTabBar::tab {
            background: #3c3c3c;
            color: #e0e0e0;
            padding: 10px 15px;
            border: 1px solid #555;
            border-radius: 5px 0 0 5px;
            margin: 2px;
        }
        QTabBar::tab:selected {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                       stop:0 #6a5acd, stop:1 #483d8b);
            color: white;
            font-weight: bold;
        }
        QTabBar::tab:hover {
            background: #505050;
        }
    )");
}

void CharacterBuilderWindow::setupMenuBar() {
    QMenuBar* menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    // File menu
    QMenu* fileMenu = menuBar->addMenu("&File");

    newAction = new QAction("&New Card", this);
    newAction->setShortcut(QKeySequence::New);
    fileMenu->addAction(newAction);

    openAction = new QAction("&Open Card", this);
    openAction->setShortcut(QKeySequence::Open);
    fileMenu->addAction(openAction);

    saveAction = new QAction("&Save Card", this);
    saveAction->setShortcut(QKeySequence::Save);
    fileMenu->addAction(saveAction);

    saveAsAction = new QAction("Save Card &As...", this);
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    fileMenu->addAction(saveAsAction);

    fileMenu->addSeparator();

    importAction = new QAction("&Import Card...", this);
    fileMenu->addAction(importAction);

    exportAction = new QAction("&Export Card...", this);
    fileMenu->addAction(exportAction);

    fileMenu->addSeparator();

    QAction* exitAction = new QAction("E&xit", this);
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
    fileMenu->addAction(exitAction);

    // Tools menu
    QMenu* toolsMenu = menuBar->addMenu("&Tools");

    wizardAction = new QAction("&Guided Wizard", this);
    toolsMenu->addAction(wizardAction);

    validateAction = new QAction("&Validate Card", this);
    toolsMenu->addAction(validateAction);

    modeToggleAction = new QAction("Switch to &Advanced Mode", this);
    toolsMenu->addAction(modeToggleAction);

    toolsMenu->addSeparator();

    importKinksAction = new QAction("Import &Kinks Database...", this);
    toolsMenu->addAction(importKinksAction);

    // Presets menu
    QMenu* presetsMenu = menuBar->addMenu("&Presets");

    loadPresetAction = new QAction("&Load Preset...", this);
    presetsMenu->addAction(loadPresetAction);

    savePresetAction = new QAction("&Save as Preset...", this);
    presetsMenu->addAction(savePresetAction);
}

void CharacterBuilderWindow::setupToolBar() {
    toolBar = addToolBar("Main Toolbar");
    toolBar->setMovable(false);

    toolBar->addAction(newAction);
    toolBar->addAction(openAction);
    toolBar->addAction(saveAction);
    toolBar->addSeparator();
    toolBar->addAction(importAction);
    toolBar->addAction(exportAction);
    toolBar->addSeparator();
    toolBar->addAction(wizardAction);
    toolBar->addAction(validateAction);
    toolBar->addSeparator();
    toolBar->addAction(modeToggleAction);

    toolBar->setStyleSheet(R"(
        QToolBar {
            background: #3a3a3a;
            border: none;
            spacing: 5px;
            padding: 5px;
        }
        QToolButton {
            background: #4a4a4a;
            color: #e0e0e0;
            border: 1px solid #555;
            border-radius: 3px;
            padding: 5px;
        }
        QToolButton:hover {
            background: #5a5a5a;
        }
        QToolButton:pressed {
            background: #6a5acd;
        }
    )");
}

void CharacterBuilderWindow::setupStatusBar() {
    statusBar = new QStatusBar(this);
    setStatusBar(statusBar);

    validationStatusLabel = new QLabel("✓ Valid", this);
    validationStatusLabel->setStyleSheet("color: #4CAF50; font-weight: bold;");
    statusBar->addPermanentWidget(validationStatusLabel);

    statusBar->setStyleSheet(R"(
        QStatusBar {
            background: #2a2a2a;
            color: #e0e0e0;
            border-top: 1px solid #444;
        }
    )");
}

void CharacterBuilderWindow::createPanels() {
    basicInfoPanel = new BasicInfoPanel(currentCard, this);
    tabWidget->addTab(basicInfoPanel, "📝 Basic Info");

    personalityPanel = new PersonalityPanel(currentCard, this);
    tabWidget->addTab(personalityPanel, "🎭 Personality");

    memoryLorePanel = new MemoryLorePanel(currentCard, this);
    tabWidget->addTab(memoryLorePanel, "🧠 Memory & Lore");

    dialoguePanel = new DialoguePanel(currentCard, this);
    tabWidget->addTab(dialoguePanel, "💬 Dialogues");

    worldBuilderPanel = new WorldBuilderPanel(currentCard, this);
    tabWidget->addTab(worldBuilderPanel, "🌍 World Builder");

    portraitPanel = new PortraitPanel(currentCard, this);
    tabWidget->addTab(portraitPanel, "🖼️ Portrait");
}

void CharacterBuilderWindow::connectSignals() {
    connect(newAction, &QAction::triggered, this, &CharacterBuilderWindow::onNewCard);
    connect(openAction, &QAction::triggered, this, &CharacterBuilderWindow::onOpenCard);
    connect(saveAction, &QAction::triggered, this, &CharacterBuilderWindow::onSaveCard);
    connect(saveAsAction, &QAction::triggered, this, &CharacterBuilderWindow::onSaveCardAs);
    connect(importAction, &QAction::triggered, this, &CharacterBuilderWindow::onImportCard);
    connect(exportAction, &QAction::triggered, this, &CharacterBuilderWindow::onExportCard);
    connect(validateAction, &QAction::triggered, this, &CharacterBuilderWindow::onValidateCard);
    connect(wizardAction, &QAction::triggered, this, &CharacterBuilderWindow::onShowWizard);
    connect(modeToggleAction, &QAction::triggered, this, &CharacterBuilderWindow::onSwitchMode);
    connect(loadPresetAction, &QAction::triggered, this, &CharacterBuilderWindow::onLoadPreset);
    connect(savePresetAction, &QAction::triggered, this, &CharacterBuilderWindow::onSaveAsPreset);
    connect(importKinksAction, &QAction::triggered, this, &CharacterBuilderWindow::onImportKinks);

    // Connect panel modification signals
    connect(basicInfoPanel, &BasicInfoPanel::modified, this, &CharacterBuilderWindow::onCardModified);
    connect(personalityPanel, &PersonalityPanel::modified, this, &CharacterBuilderWindow::onCardModified);
    connect(memoryLorePanel, &MemoryLorePanel::modified, this, &CharacterBuilderWindow::onCardModified);
    connect(dialoguePanel, &DialoguePanel::modified, this, &CharacterBuilderWindow::onCardModified);
    connect(worldBuilderPanel, &WorldBuilderPanel::modified, this, &CharacterBuilderWindow::onCardModified);
    connect(portraitPanel, &PortraitPanel::modified, this, &CharacterBuilderWindow::onCardModified);
}

void CharacterBuilderWindow::onNewCard() {
    if (!promptSaveIfModified()) {
        return;
    }

    currentCard = std::make_shared<CharacterCardData>();
    currentFilepath.clear();
    isModified = false;

    // Refresh all panels
    basicInfoPanel->setCard(currentCard);
    personalityPanel->setCard(currentCard);
    memoryLorePanel->setCard(currentCard);
    dialoguePanel->setCard(currentCard);
    worldBuilderPanel->setCard(currentCard);
    portraitPanel->setCard(currentCard);

    updateTitle();
    updateValidationStatus();

    statusBar->showMessage("New card created", 3000);
}

void CharacterBuilderWindow::onOpenCard() {
    if (!promptSaveIfModified()) {
        return;
    }

    QString filepath = QFileDialog::getOpenFileName(
        this,
        "Open Character Card",
        "",
        "Character Cards (*.json *.png);;JSON Files (*.json);;PNG Files (*.png);;All Files (*)"
    );

    if (!filepath.isEmpty()) {
        loadCard(filepath.toStdString());
    }
}

void CharacterBuilderWindow::onSaveCard() {
    if (currentFilepath.empty()) {
        onSaveCardAs();
    } else {
        saveCard(currentFilepath);
    }
}

void CharacterBuilderWindow::onSaveCardAs() {
    QString filepath = QFileDialog::getSaveFileName(
        this,
        "Save Character Card",
        "",
        "JSON Files (*.json);;All Files (*)"
    );

    if (!filepath.isEmpty()) {
        saveCard(filepath.toStdString());
    }
}

void CharacterBuilderWindow::onImportCard() {
    QString filepath = QFileDialog::getOpenFileName(
        this,
        "Import Character Card",
        "",
        "All Supported (*.json *.png);;JSON Files (*.json);;PNG Files (*.png);;All Files (*)"
    );

    if (!filepath.isEmpty()) {
        importCard(filepath.toStdString());
    }
}

void CharacterBuilderWindow::onExportCard() {
    ExportDialog dialog(currentCard, this);
    dialog.exec();
}

void CharacterBuilderWindow::onValidateCard() {
    updateValidationStatus();

    auto issues = validator.validate(*currentCard);
    QString report = QString::fromStdString(validator.formatReport(issues));

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Card Validation");

    ValidationLevel status = validator.getOverallStatus(issues);
    if (status == ValidationLevel::Error) {
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Validation Failed");
    } else if (status == ValidationLevel::Warning) {
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Validation Passed with Warnings");
    } else {
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Validation Passed");
    }

    msgBox.setDetailedText(report);
    msgBox.exec();
}

void CharacterBuilderWindow::onCardModified() {
    isModified = true;
    updateTitle();
    updateValidationStatus();
}

void CharacterBuilderWindow::onSwitchMode() {
    isSimpleMode = !isSimpleMode;

    if (isSimpleMode) {
        modeToggleAction->setText("Switch to &Advanced Mode");
        statusBar->showMessage("Switched to Simple Mode", 3000);
    } else {
        modeToggleAction->setText("Switch to &Simple Mode");
        statusBar->showMessage("Switched to Advanced Mode", 3000);
    }

    // Update all panels to reflect mode change
    basicInfoPanel->setSimpleMode(isSimpleMode);
    personalityPanel->setSimpleMode(isSimpleMode);
    memoryLorePanel->setSimpleMode(isSimpleMode);
}

void CharacterBuilderWindow::onShowWizard() {
    WizardDialog wizard(currentCard, this);
    if (wizard.exec() == QDialog::Accepted) {
        // Refresh all panels
        basicInfoPanel->refresh();
        personalityPanel->refresh();
        memoryLorePanel->refresh();
        dialoguePanel->refresh();

        onCardModified();
        statusBar->showMessage("Card updated from wizard", 3000);
    }
}

void CharacterBuilderWindow::onLoadPreset() {
    // Implementation for loading presets
    statusBar->showMessage("Load preset feature coming soon", 3000);
}

void CharacterBuilderWindow::onSaveAsPreset() {
    // Implementation for saving presets
    statusBar->showMessage("Save preset feature coming soon", 3000);
}

void CharacterBuilderWindow::onImportKinks() {
    QProgressDialog progress("Fetching kinks database...", "Cancel", 0, 100, this);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    WebScraper scraper;
    scraper.setProgressCallback([&progress](int prog, const std::string& status) {
        progress.setValue(prog);
        progress.setLabelText(QString::fromStdString(status));
        QApplication::processEvents();
    });

    auto categories = scraper.scrapeKinksList("https://badgirlsbible.com/list-of-kinks-and-fetishes");

    progress.close();

    if (categories.empty()) {
        QMessageBox::warning(this, "Import Failed", "Failed to fetch kinks database");
        return;
    }

    // Add kinks to the current card
    for (const auto& category : categories) {
        for (const auto& kink : category.items) {
            currentCard->kinks_fetishes.push_back(kink);
        }
    }

    QMessageBox::information(this, "Import Successful",
                            QString("Imported %1 kinks/fetishes").arg(currentCard->kinks_fetishes.size()));

    onCardModified();
}

void CharacterBuilderWindow::loadCard(const std::string& filepath) {
    CardImporter importer;
    auto result = importer.importFromFile(filepath);

    if (!result.success) {
        QMessageBox::critical(this, "Load Failed", QString::fromStdString(result.error_message));
        return;
    }

    currentCard = result.card;
    currentFilepath = filepath;
    isModified = false;

    // Refresh all panels
    basicInfoPanel->setCard(currentCard);
    personalityPanel->setCard(currentCard);
    memoryLorePanel->setCard(currentCard);
    dialoguePanel->setCard(currentCard);
    worldBuilderPanel->setCard(currentCard);
    portraitPanel->setCard(currentCard);

    updateTitle();
    updateValidationStatus();

    statusBar->showMessage("Card loaded successfully", 3000);
}

void CharacterBuilderWindow::saveCard(const std::string& filepath) {
    try {
        nlohmann::json j = currentCard->toJson();

        std::ofstream file(filepath);
        if (!file) {
            QMessageBox::critical(this, "Save Failed", "Could not open file for writing");
            return;
        }

        file << j.dump(2); // Pretty print with 2-space indent
        file.close();

        currentFilepath = filepath;
        isModified = false;

        updateTitle();
        statusBar->showMessage("Card saved successfully", 3000);

    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Save Failed", QString("Error: %1").arg(e.what()));
    }
}

void CharacterBuilderWindow::importCard(const std::string& filepath) {
    loadCard(filepath);
}

void CharacterBuilderWindow::updateTitle() {
    QString title = "Character Card Builder";

    if (!currentCard->name.empty()) {
        title += " - " + QString::fromStdString(currentCard->name);
    }

    if (isModified) {
        title += " *";
    }

    setWindowTitle(title);
}

void CharacterBuilderWindow::updateValidationStatus() {
    auto issues = validator.validate(*currentCard);
    ValidationLevel status = validator.getOverallStatus(issues);

    if (status == ValidationLevel::Error) {
        validationStatusLabel->setText("❌ Invalid");
        validationStatusLabel->setStyleSheet("color: #f44336; font-weight: bold;");
    } else if (status == ValidationLevel::Warning) {
        validationStatusLabel->setText("⚠️ Warnings");
        validationStatusLabel->setStyleSheet("color: #ff9800; font-weight: bold;");
    } else {
        validationStatusLabel->setText("✓ Valid");
        validationStatusLabel->setStyleSheet("color: #4CAF50; font-weight: bold;");
    }
}

bool CharacterBuilderWindow::promptSaveIfModified() {
    if (!isModified) {
        return true;
    }

    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Unsaved Changes",
        "Do you want to save your changes?",
        QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel
    );

    if (reply == QMessageBox::Yes) {
        onSaveCard();
        return !isModified; // If still modified, save was cancelled
    } else if (reply == QMessageBox::No) {
        return true;
    } else {
        return false; // Cancel
    }
}

void CharacterBuilderWindow::closeEvent(QCloseEvent* event) {
    if (promptSaveIfModified()) {
        event->accept();
    } else {
        event->ignore();
    }
}

} // namespace CharacterCard
} // namespace AutoCoder

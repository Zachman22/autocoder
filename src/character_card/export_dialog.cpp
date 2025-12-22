#include "character_card/export_dialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <fstream>

namespace AutoCoder {
namespace CharacterCard {

ExportDialog::ExportDialog(std::shared_ptr<CharacterCardData> card, QWidget* parent)
    : QDialog(parent), currentCard(card) {
    setupUi();
}

void ExportDialog::setupUi() {
    setWindowTitle("Export Character Card");
    resize(500, 200);
    
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    
    jsonRadio = new QRadioButton("JSON (.json)", this);
    jsonRadio->setChecked(true);
    pngRadio = new QRadioButton("PNG Card (.png)", this);
    txtRadio = new QRadioButton("Text Prompt (.txt)", this);
    
    mainLayout->addWidget(jsonRadio);
    mainLayout->addWidget(pngRadio);
    mainLayout->addWidget(txtRadio);
    
    QHBoxLayout* pathLayout = new QHBoxLayout();
    filepathEdit = new QLineEdit(this);
    browseButton = new QPushButton("Browse...", this);
    connect(browseButton, &QPushButton::clicked, this, &ExportDialog::onBrowse);
    pathLayout->addWidget(filepathEdit);
    pathLayout->addWidget(browseButton);
    mainLayout->addLayout(pathLayout);
    
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    exportButton = new QPushButton("Export", this);
    QPushButton* cancelButton = new QPushButton("Cancel", this);
    connect(exportButton, &QPushButton::clicked, this, &ExportDialog::onExport);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    buttonLayout->addWidget(exportButton);
    buttonLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonLayout);
}

void ExportDialog::onBrowse() {
    QString filter = "All Files (*)";
    if (jsonRadio->isChecked()) filter = "JSON Files (*.json)";
    else if (pngRadio->isChecked()) filter = "PNG Files (*.png)";
    else if (txtRadio->isChecked()) filter = "Text Files (*.txt)";
    
    QString filename = QFileDialog::getSaveFileName(this, "Export Card", "", filter);
    if (!filename.isEmpty()) {
        filepathEdit->setText(filename);
    }
}

void ExportDialog::onExport() {
    std::string filepath = filepathEdit->text().toStdString();
    if (filepath.empty()) {
        QMessageBox::warning(this, "Export Failed", "Please specify a file path");
        return;
    }
    
    try {
        if (jsonRadio->isChecked()) {
            exportAsJson(filepath);
        } else if (pngRadio->isChecked()) {
            exportAsPng(filepath);
        } else if (txtRadio->isChecked()) {
            exportAsTxt(filepath);
        }
        
        QMessageBox::information(this, "Export Successful", "Card exported successfully!");
        accept();
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Export Failed", QString("Error: %1").arg(e.what()));
    }
}

void ExportDialog::exportAsJson(const std::string& filepath) {
    nlohmann::json j = currentCard->toSillyTavernJson();
    std::ofstream file(filepath);
    file << j.dump(2);
}

void ExportDialog::exportAsPng(const std::string& filepath) {
    // PNG export with embedded JSON (stub)
    exportAsJson(filepath + ".json");
}

void ExportDialog::exportAsTxt(const std::string& filepath) {
    std::ofstream file(filepath);
    file << currentCard->generatePrompt();
}

} // namespace CharacterCard
} // namespace AutoCoder

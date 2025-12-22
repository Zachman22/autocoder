#ifndef EXPORT_DIALOG_H
#define EXPORT_DIALOG_H

#include <QDialog>
#include <QRadioButton>
#include <QPushButton>
#include <QLineEdit>
#include <memory>

#include "character_card/card_data.h"

namespace AutoCoder {
namespace CharacterCard {

class ExportDialog : public QDialog {
    Q_OBJECT

public:
    explicit ExportDialog(std::shared_ptr<CharacterCardData> card, QWidget* parent = nullptr);
    ~ExportDialog() override = default;

private slots:
    void onExport();
    void onBrowse();

private:
    void setupUi();
    void exportAsJson(const std::string& filepath);
    void exportAsPng(const std::string& filepath);
    void exportAsTxt(const std::string& filepath);

    std::shared_ptr<CharacterCardData> currentCard;

    QRadioButton* jsonRadio;
    QRadioButton* pngRadio;
    QRadioButton* txtRadio;
    QLineEdit* filepathEdit;
    QPushButton* browseButton;
    QPushButton* exportButton;
};

} // namespace CharacterCard
} // namespace AutoCoder

#endif // EXPORT_DIALOG_H

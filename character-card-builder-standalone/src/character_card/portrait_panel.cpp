#include "character_card/portrait_panel.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include <QPixmap>

namespace AutoCoder {
namespace CharacterCard {

PortraitPanel::PortraitPanel(std::shared_ptr<CharacterCardData> card, QWidget* parent)
    : QWidget(parent), currentCard(card) {
    setupUi();
    loadFromCard();
}

void PortraitPanel::setupUi() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    
    imageLabel = new QLabel(this);
    imageLabel->setMinimumSize(400, 400);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setStyleSheet("QLabel { border: 2px solid #555; background: #333; }");
    imageLabel->setText("No portrait loaded");
    mainLayout->addWidget(imageLabel, 0, Qt::AlignCenter);
    
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    loadButton = new QPushButton("Load Image", this);
    clearButton = new QPushButton("Clear", this);
    generateButton = new QPushButton("Generate (AI)", this);
    
    connect(loadButton, &QPushButton::clicked, this, &PortraitPanel::onLoadImage);
    connect(clearButton, &QPushButton::clicked, this, &PortraitPanel::onClearImage);
    connect(generateButton, &QPushButton::clicked, this, &PortraitPanel::onGenerateImage);
    
    buttonLayout->addWidget(loadButton);
    buttonLayout->addWidget(clearButton);
    buttonLayout->addWidget(generateButton);
    mainLayout->addLayout(buttonLayout);
    
    mainLayout->addStretch();
}

void PortraitPanel::setCard(std::shared_ptr<CharacterCardData> card) {
    currentCard = card;
    loadFromCard();
}

void PortraitPanel::refresh() {
    loadFromCard();
}

void PortraitPanel::loadFromCard() {
    displayImage();
}

void PortraitPanel::displayImage() {
    if (!currentCard || currentCard->portrait_path.empty()) {
        imageLabel->setText("No portrait loaded");
        return;
    }
    
    QPixmap pixmap(QString::fromStdString(currentCard->portrait_path));
    if (!pixmap.isNull()) {
        imageLabel->setPixmap(pixmap.scaled(400, 400, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

void PortraitPanel::onLoadImage() {
    QString filename = QFileDialog::getOpenFileName(this, "Load Portrait", "", "Images (*.png *.jpg *.jpeg *.bmp)");
    if (!filename.isEmpty() && currentCard) {
        currentCard->portrait_path = filename.toStdString();
        displayImage();
        emit modified();
    }
}

void PortraitPanel::onClearImage() {
    if (currentCard) {
        currentCard->portrait_path.clear();
        imageLabel->setText("No portrait loaded");
        emit modified();
    }
}

void PortraitPanel::onGenerateImage() {
    // Placeholder for AI image generation
    emit modified();
}

} // namespace CharacterCard
} // namespace AutoCoder

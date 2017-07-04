#include "view_page_newreminder.h"
#include <iostream>

ViewPageNewReminder::ViewPageNewReminder(QWidget* parent) :
	ViewPage("Nuovo promemoria", parent),
	layout(new QVBoxLayout(this)),
	formContainer(new QWidget(this)),
	formLayout(new QFormLayout(formContainer)),
	titleEdit(new QLineEdit(formContainer)),
	descriptionEdit(new QTextEdit(formContainer)),
	categoryEdit(new QLineEdit(formContainer)),
	targetCombo(new QComboBox(formContainer)),
	specificTargetEdit(new QLineEdit(formContainer)),
	typeCombo(new QComboBox(formContainer)),
	imageUrl(""),
	imageSelector(new QFileDialog(formContainer)),
	imageSelectorButton(new QPushButton("Scegli immagine..", formContainer)),
	submitButton(new QPushButton("Crea", formContainer))
{


	descriptionEdit->setStyleSheet("font-size: 16px;");
	targetCombo->addItem("Tutti");
	targetCombo->addItem("Privato");
	targetCombo->addItem("Genitori");
	targetCombo->addItem("Figli");
	targetCombo->addItem("Ospiti");
	typeCombo->addItem("Testo");
	typeCombo->addItem("Testo con immagine");
	submitButton->setCursor(Qt::PointingHandCursor);

	connect(targetCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(onTargetChanged(int)));
	connect(typeCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(onTypeChanged(int)));
	connect(imageSelectorButton, SIGNAL(clicked(bool)), this, SLOT(onImageSelectorButtonClicked()));
	connect(imageSelector, SIGNAL(fileSelected(QString)), this, SLOT(onImageSelectorFinished(QString)));
	connect(submitButton, SIGNAL(clicked(bool)), this, SIGNAL(formSubmitted()));

	formLayout->setFormAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
	formLayout->addRow("Titolo: ", titleEdit);
	formLayout->addRow("Descrizione: ", descriptionEdit);
	formLayout->addRow("Categoria: ", categoryEdit);
	formLayout->addRow("Destinazione: ", targetCombo);
	formLayout->addRow("Username utente destinazione: ", specificTargetEdit);
	formLayout->addRow("Tipo: ", typeCombo);
	formLayout->addRow(imageSelectorButton);
	formLayout->addRow(submitButton);
	formContainer->setLayout(formLayout);
	onTargetChanged(2); //workarround just to hide the specificaTargetEdit
	onTypeChanged(2); //workarround for same reason for imageSelector
	layout->setContentsMargins(200,0,200,0);
	layout->addWidget(formContainer);
	setLayout(layout);
	hide();
}

void ViewPageNewReminder::onTargetChanged(int idx) {
	if(idx==1) {
		formLayout->labelForField(specificTargetEdit)->show();
		specificTargetEdit->show();
	} else {
		formLayout->labelForField(specificTargetEdit)->hide();
		specificTargetEdit->hide();
	}
}

void ViewPageNewReminder::onTypeChanged(int idx) {
	if(idx==1)
		imageSelectorButton->show();
	else
		imageSelectorButton->hide();

}

void ViewPageNewReminder::onImageSelectorButtonClicked() {
	imageSelector->show();
}

void ViewPageNewReminder::onImageSelectorFinished(const QString& s) {
	imageUrl=s;
}

QString ViewPageNewReminder::getTitle() const {
	return titleEdit->text();
}

QString ViewPageNewReminder::getDescription() const {
	return descriptionEdit->toPlainText();
}

QString ViewPageNewReminder::getCategory() const {
	return categoryEdit->text();
}

int ViewPageNewReminder::getTargetType() const {
	return targetCombo->currentIndex();
}

QString ViewPageNewReminder::getSpecificTargetUsername() const {
	return specificTargetEdit->text();
}

int ViewPageNewReminder::getReminderType() const {
	return typeCombo->currentIndex();
}

QString ViewPageNewReminder::getImageUrl() const {
	return imageUrl;
}

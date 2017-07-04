#include "view_singlereminderrow.h"

ViewSingleReminderRow::ViewSingleReminderRow(const ModelReminder* reminder, QWidget* parent):
	View(parent),
	idEdit(new QLineEdit(QString::fromStdString(std::to_string(reminder->getID())),this)),
	titleEdit(new QLineEdit(reminder->getTitle(),this)),
	descriptionEdit(new QLineEdit(reminder->getDescription(), this)),
	categoryEdit(new QLineEdit(reminder->getCategory(), this)),
	authorEdit(new QLineEdit(reminder->getUsernameAuthor(), this)),
	targetCombo(new QComboBox(this)),
	specificTargetEdit(new QLineEdit(reminder->getUsernameSpecificTarget(), this)),
	updateButton(new QPushButton("Aggiorna", this)),
	deleteButton(new QPushButton("X", this))
{

	updateButton->setCursor(Qt::PointingHandCursor);
	deleteButton->setCursor(Qt::PointingHandCursor);

	targetCombo->addItem("Per Tutti");
	targetCombo->addItem("Privato");
	targetCombo->addItem("Per Genitori");
	targetCombo->addItem("Per Figli");
	targetCombo->addItem("Per Ospiti");
	targetCombo->setCurrentIndex(reminder->getTarget());

	if(targetCombo->currentIndex()!=1)
		specificTargetEdit->setEnabled(false);


	idEdit->setEnabled(false);
	authorEdit->setEnabled(false);
	connect(targetCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(onTargetChanged(int)));
	connect(updateButton, SIGNAL(clicked(bool)), this, SIGNAL(updateReminderClicked()));
	connect(deleteButton, SIGNAL(clicked(bool)), this, SIGNAL(deleteReminderClicked()));

	setMinimumWidth(700);
	setMaximumWidth(1000);
}

void ViewSingleReminderRow::insertIntoGridLayout(QGridLayout *listLayout, int curRow) const {
	listLayout->addWidget(idEdit, curRow, 0, Qt::AlignHCenter);
	listLayout->addWidget(titleEdit, curRow, 1, Qt::AlignHCenter);
	listLayout->addWidget(descriptionEdit, curRow, 2);
	listLayout->addWidget(categoryEdit, curRow, 3, Qt::AlignHCenter);
	listLayout->addWidget(authorEdit, curRow, 4, Qt::AlignHCenter);
	listLayout->addWidget(targetCombo, curRow, 5, Qt::AlignHCenter);
	listLayout->addWidget(specificTargetEdit, curRow, 6, Qt::AlignHCenter);
	listLayout->addWidget(updateButton, curRow, 7, Qt::AlignHCenter);
	listLayout->addWidget(deleteButton, curRow, 8, Qt::AlignHCenter);
}

void ViewSingleReminderRow::onTargetChanged(int idx) {
	if(idx==1)
		specificTargetEdit->setEnabled(true);
	else
		specificTargetEdit->setEnabled(false);

}


int ViewSingleReminderRow::getID() const {
	return std::stoi(idEdit->text().toStdString());
}

QString ViewSingleReminderRow::getTitle() const {
	return titleEdit->text();
}

QString ViewSingleReminderRow::getDescription() const {
	return descriptionEdit->text();
}

QString ViewSingleReminderRow::getCategory() const {
	return categoryEdit->text();
}

QString ViewSingleReminderRow::getAuthor() const {
	return authorEdit->text();
}

QString ViewSingleReminderRow::getSpecificTarget() const {
	return specificTargetEdit->text();
}

int ViewSingleReminderRow::getTarget() const {
	return targetCombo->currentIndex();
}

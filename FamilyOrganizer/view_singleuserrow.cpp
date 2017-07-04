#include "view_singleuserrow.h"


ViewSingleUserRow::ViewSingleUserRow(const ModelUser* user, int userType, QWidget* parent):
	View(parent),
	nameEdit(new QLineEdit(user->getName(), this)),
	userEdit(new QLineEdit(user->getUsername(), this)),
	passEdit(new QLineEdit("xxxxx", this)),
	userTypeCombo(new QComboBox(this)),
	canCreateUsersCheck(new QCheckBox("Può creare utenti", this)),
	canCreateRemindersCheck(new QCheckBox("Può creare promemorie", this)),
	permissionsContainer(new QWidget(this)),
	updateButton(new QPushButton("Aggiorna", this)),
	deleteButton(new QPushButton("X", this))
{
	updateButton->setCursor(Qt::PointingHandCursor);
	deleteButton->setCursor(Qt::PointingHandCursor);

	passEdit->setEchoMode(QLineEdit::Password);
	passEdit->setEnabled(false);
	userEdit->setEnabled(false);
	userTypeCombo->addItem("Genitore");
	userTypeCombo->addItem("Figlio");
	userTypeCombo->addItem("Ospite");
	userTypeCombo->setCurrentIndex(userType);

	canCreateUsersCheck->setChecked(user->getPermissions().testFlag(ModelUser::CreateUsers));
	canCreateRemindersCheck->setChecked(user->getPermissions().testFlag(ModelUser::CreateReminders));

	connect(updateButton, SIGNAL(clicked(bool)), this, SIGNAL(updateUserClicked()));
	connect(deleteButton, SIGNAL(clicked(bool)), this, SIGNAL(deleteUserClicked()));

	auto layoutPermissions = new QVBoxLayout(permissionsContainer);
	permissionsContainer->setLayout(layoutPermissions);
	layoutPermissions->addWidget(canCreateUsersCheck);
	layoutPermissions->addWidget(canCreateRemindersCheck);

}

void ViewSingleUserRow::insertIntoGridLayout(QGridLayout* listLayout, int curRow) const {
	listLayout->addWidget(nameEdit, curRow, 0, Qt::AlignHCenter);
	listLayout->addWidget(userEdit, curRow, 1);
	listLayout->addWidget(passEdit, curRow, 2);
	listLayout->addWidget(userTypeCombo, curRow, 3);
	listLayout->addWidget(permissionsContainer, curRow, 4);
	listLayout->addWidget(updateButton, curRow, 5);
	listLayout->addWidget(deleteButton, curRow, 6);
}

QString ViewSingleUserRow::getName() const {
	return this->nameEdit->text();
}

QString ViewSingleUserRow::getUsername() const {
	return this->userEdit->text();
}

int ViewSingleUserRow::getUserType() const {
	return this->userTypeCombo->currentIndex();
}

ModelUser::Permissions ViewSingleUserRow::getPermissions() const {
	return ModelUser::Permissions((canCreateUsersCheck->isChecked()?ModelUser::CreateUsers:0)
											|(canCreateRemindersCheck->isChecked()?ModelUser::CreateReminders:0));
}

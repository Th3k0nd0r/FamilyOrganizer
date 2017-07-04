#include "view_page_newuser.h"
#include <iostream>

ViewPageNewUser::ViewPageNewUser(QWidget* parent):
	ViewPage("Aggiungi nuovo utente", parent),
	layout(new QVBoxLayout(this)),
	formContainer(new QWidget(this)),
	formLayout(new QFormLayout(formContainer)),
	nameEdit(new QLineEdit(formContainer)),
	userEdit(new QLineEdit(formContainer)),
	passEdit(new QLineEdit(formContainer)),
	createUsersPermissionCheck(new QCheckBox("Può creare utenti", formContainer)),
	createRemindersPermissionCheck(new QCheckBox("Può creare promemorie", formContainer)),
	userTypeCombo(new QComboBox(formContainer)),
	submitButton(new QPushButton("Crea", formContainer))
{

	passEdit->setEchoMode(QLineEdit::Password);

	userTypeCombo->addItem("Genitore");
	userTypeCombo->addItem("Figlio");
	userTypeCombo->addItem("Ospite");

	connect(submitButton, SIGNAL(clicked(bool)), this, SIGNAL(formSubmitted()));

	formLayout->setFormAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
	formLayout->addRow("Nome: ", nameEdit);
	formLayout->addRow("Username: ", userEdit);
	formLayout->addRow("Password: ", passEdit);
	formLayout->addRow("Tipo utente: ", userTypeCombo);
	formLayout->addRow(createUsersPermissionCheck);
	formLayout->addRow(createRemindersPermissionCheck);
	formLayout->addRow(submitButton);
	formContainer->setLayout(formLayout);
	layout->setContentsMargins(200,0,200,0);
	layout->addWidget(formContainer);
	setLayout(layout);
	hide();
}

QString ViewPageNewUser::getName() const {
	return nameEdit->text();
}

QString ViewPageNewUser::getUsername() const {
	return userEdit->text();
}

QString ViewPageNewUser::getPassword() const {
	return passEdit->text();
}

int ViewPageNewUser::getUserType() const {
	return userTypeCombo->currentIndex();
}

bool ViewPageNewUser::hasCreateUsersPermission() const {
	return createUsersPermissionCheck->isChecked();
}

bool ViewPageNewUser::hasCreateRemindersPermission() const {
	return createRemindersPermissionCheck->isChecked();
}

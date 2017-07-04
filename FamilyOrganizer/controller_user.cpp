#include "controller_user.h"
#include <iostream>
#include <QMessageBox>

#include <model_parentuser.h>
#include <model_childuser.h>
#include <model_guestuser.h>
#include <view_mainwindow.h>
#include <view_page_newuser.h>
#include <view_page_manageusers.h>

ControllerUser::ControllerUser() :
    currentUser(nullptr)
{
	wholeFamily.readFromFile();
}

ModelUser* ControllerUser::getCurrentUser() const {
	return currentUser;
}

void ControllerUser::onLoginFormSubmitted() {
	auto a = qobject_cast<ViewPageLogin*>(sender());
	if(!a)
		return;

	if(auto foundUser = wholeFamily.getUser(a->getUsername())) {
		if(foundUser->checkLogin(a->getPassword())) {
			//Login success
			currentUser=foundUser;
			emit userLoggedIn();
		} else
			QMessageBox::information(a, "Impossibile effettuare il login",
									 "Password non corretta, riprovare.", QMessageBox::Ok);
	} else
		QMessageBox::information(a, "Impossibile effettuare il login",
								 "Utente non esistente, riprovare.", QMessageBox::Ok);

}

void ControllerUser::onNewUserFormSubmitted() {
	auto a = qobject_cast<ViewPageNewUser*>(sender());

	if(!a)
		return;
	if(a->getUsername().isEmpty() ||
			a->getName().isEmpty() ||
			a->getPassword().isEmpty())
		QMessageBox::information(a, "Errore",
								 "Compilare tutti i campi e riprovare.", QMessageBox::Ok);
	else if(wholeFamily.userExists(a->getUsername()))
		QMessageBox::information(a, "Errore",
								 "Esiste già un utente con lo stesso username.", QMessageBox::Ok);
	else {
		int userType = a->getUserType();
		ModelUser::Permissions userPermissions((a->hasCreateRemindersPermission() ? ModelUser::CreateReminders : 0)
											   | (a->hasCreateUsersPermission() ? ModelUser::CreateUsers : 0));

		switch(userType) {
		case 0:
			wholeFamily.addNewUser(new ModelParentUser(a->getName(), a->getUsername(), a->getPassword(), userPermissions));
			break;
		case 1:
			wholeFamily.addNewUser(new ModelChildUser(a->getName(), a->getUsername(), a->getPassword(), userPermissions));
			break;
		case 2:
			wholeFamily.addNewUser(new ModelGuestUser(a->getName(), a->getUsername(), a->getPassword(), userPermissions));
			break;
		}
		QMessageBox::information(a, "Successo", "Utente creato con successo!", QMessageBox::Ok);
	}

}

void ControllerUser::onRequestAllUsers() const {
	emit updateUsers(wholeFamily.getAllUsers());
}

void ControllerUser::onRequestUpdateUser(const QString& pName, const QString& pUser, const int userType, ModelUser::Permissions pUserPermissions) {
	auto a = qobject_cast<ViewPageManageUsers*>(sender());
	if(!a)
		return;
	if(pName.isEmpty()) {
		QMessageBox::information(a, "Errore", "Inserire il nome e riprovare.", QMessageBox::Ok);
		return;
	}

	auto userToUpdate = wholeFamily.getUser(pUser);
	ModelUser* newUser=0;
	bool differentType = true;

	//Check if it's requested a different usertype
	if(userType==0 && !dynamic_cast<ModelParentUser*>(userToUpdate))
		newUser = new ModelParentUser(pName, pUser,"", pUserPermissions);
	else if(userType==1 && !dynamic_cast<ModelChildUser*>(userToUpdate))
		newUser = new ModelChildUser(pName, pUser, "", pUserPermissions);
	else if(userType==2 && !dynamic_cast<ModelGuestUser*>(userToUpdate))
		newUser = new ModelGuestUser(pName, pUser, "", pUserPermissions);
	else
		differentType=false;

	if(!differentType) {
		userToUpdate->setName(pName);
		userToUpdate->setPermissions(pUserPermissions);
	} else {
		newUser->setPassword(userToUpdate->getPassword(), true);
		wholeFamily.deleteUser(pUser);
		wholeFamily.addNewUser(newUser);
	}
	QMessageBox::information(a, "Successo", "Utente aggiornato con successo!", QMessageBox::Ok);
	emit updateUsers(wholeFamily.getAllUsers());
}

void ControllerUser::onRequestDeleteUser(const QString& pUsername) {
	auto a = qobject_cast<ViewPageManageUsers*>(sender());
	if(!a)
		return;
	wholeFamily.deleteUser(pUsername);
	emit updateUsers(wholeFamily.getAllUsers());
	QMessageBox::information(a, "Successo", "Utente eliminato con successo!", QMessageBox::Ok);
}

 void ControllerUser::onSaveOnDisk() {
	 auto a = qobject_cast<ViewMainWindow*>(sender());
	 if(!a)
		 return;
	 if(!wholeFamily.saveToFile())
		 QMessageBox::information(a, "Errore", "Impossibile salvare gli utenti su disco.", QMessageBox::Ok);

 }

#ifndef CONTROLLER_USER_H
#define CONTROLLER_USER_H

#include <QObject>
#include <view_page_login.h>
#include <model_family.h>

class ControllerUser : public QObject {

Q_OBJECT

private:
	ModelFamily wholeFamily;
	ModelUser* currentUser;

public:
	ControllerUser();
	ModelUser* getCurrentUser() const;

signals:
	void userLoggedIn() const;
	void userLoggedOut() const;

	void updateUsers(const QMap<QString, ModelUser*> users) const;

public slots:
    // For signals from user forms submission (Login and New User Form)
	void onLoginFormSubmitted();
	void onNewUserFormSubmitted();

    // For signals from ManageUsers page
	void onRequestAllUsers() const;
	void onRequestUpdateUser(const QString& pName, const QString& pUser, const int userType, ModelUser::Permissions pUserPermissions);
	void onRequestDeleteUser(const QString& pUsername);

	void onSaveOnDisk();

};

#endif // CONTROLLER_USER_H

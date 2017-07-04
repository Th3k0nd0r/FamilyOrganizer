#include "controller_main.h"

#include <view_page_login.h>
#include <view_page_home.h>
#include <view_page_newuser.h>
#include <view_page_newreminder.h>
#include <view_page_manageusers.h>
#include <view_page_managereminders.h>
#include <QActionGroup>

ControllerMain::ControllerMain() :
	mainWindow(new ViewPageHome()) {}

void ControllerMain::startApp() {
    // ViewPages set init, all with parenting hierarchy
	viewPages.insert("Home", mainWindow.getHomePage());
	viewPages.insert("Login", new ViewPageLogin(&mainWindow));
	viewPages.insert("Nuovo utente", new ViewPageNewUser(&mainWindow));
	viewPages.insert("Gestione utenti", new ViewPageManageUsers(&mainWindow));
	viewPages.insert("Nuovo promemoria", new ViewPageNewReminder(&mainWindow));
	viewPages.insert("Gestione promemorie", new ViewPageManageReminders(&mainWindow));

    // Static cast mostly used viewPages, for sure static_cast doesn't fail since I just inserted
    auto homeViewPage = static_cast<ViewPageHome*>(viewPages.value("Home"));
	auto manageUsersPage = static_cast<ViewPageManageUsers*>(viewPages.value("Gestione utenti"));
	auto manageRemindersPage = static_cast<ViewPageManageReminders*>(viewPages.value("Gestione promemorie"));

	// MainWindow Menu init
	connect(mainWindow.getHeader(), SIGNAL(mainMenuActionClicked(QAction*)), this, SLOT(onMainWindowMenuActionClicked(QAction*)));

    //------ Connections between Views and Controllers using Qt signaling system -------
    //  --Controllers signals connections
	connect(&userController, SIGNAL(userLoggedIn()), this, SLOT(onUserLoggedIn()));
	connect(&remindersController, SIGNAL(onHomepageResponse(QList<ModelReminder*>)), homeViewPage, SLOT(loadReminders(QList<ModelReminder*>)));
	connect(&userController, SIGNAL(updateUsers(const QMap<QString,ModelUser*>&)), manageUsersPage, SLOT(loadUsers(const QMap<QString,ModelUser*>)));
	connect(&remindersController, SIGNAL(onShowcaseUpdated(QList<ModelReminder*>)), manageRemindersPage, SLOT(loadReminders(QList<ModelReminder*>)));

    //  --Homepage signals connections
	connect(homeViewPage, SIGNAL(requestRemindersForGuests()), &remindersController, SLOT(onRequestRemindersForGuests()));
	connect(homeViewPage, SIGNAL(requestRemindersForChildren()), &remindersController, SLOT(onRequestRemindersForChildren()));
	connect(homeViewPage, SIGNAL(requestRemindersForParents()), &remindersController, SLOT(onRequestRemindersForParents()));
	connect(homeViewPage, SIGNAL(requestRemindersForHome()), &remindersController, SLOT(onRequestRemindersForHome()));
	connect(homeViewPage, SIGNAL(requestRemindersForAll()), &remindersController, SLOT(onRequestRemindersForAll()));
	connect(homeViewPage, SIGNAL(requestPrivateReminders()), &remindersController, SLOT(onRequestPrivateReminders()));
	connect(homeViewPage, SIGNAL(requestGeneralReminders()), &remindersController, SLOT(onRequestGeneralReminders()));
	connect(homeViewPage, SIGNAL(requestFilterRemindersByCategory()), &remindersController, SLOT(onFilterRemindersByCategory()));
	connect(homeViewPage, SIGNAL(requestSentReminders()), &remindersController, SLOT(onRequestSentReminders()));

    //  --Forms signals connections
	connect(static_cast<ViewPageLogin*>(viewPages.value("Login")), SIGNAL(formSubmitted()), &userController, SLOT(onLoginFormSubmitted()));
	connect(static_cast<ViewPageNewUser*>(viewPages.value("Nuovo utente")), SIGNAL(formSubmitted()), &userController, SLOT(onNewUserFormSubmitted()));
	connect(static_cast<ViewPageNewReminder*>(viewPages.value("Nuovo promemoria")), SIGNAL(formSubmitted()), &remindersController, SLOT(onNewReminderFormSubmitted()));

    //  --ManageUsers page signals connections
	connect(manageUsersPage, SIGNAL(requestAllUsers()), &userController, SLOT(onRequestAllUsers()));
	connect(manageUsersPage, SIGNAL(requestUpdateUser(QString,QString,int,ModelUser::Permissions)), &userController, SLOT(onRequestUpdateUser(QString,QString,int,ModelUser::Permissions)));
	connect(manageUsersPage, SIGNAL(requestDeleteUser(QString)), &userController, SLOT(onRequestDeleteUser(QString)));

    //  --ManageReminders page signals connections
    connect(manageRemindersPage, SIGNAL(requestManagebleReminders()), &remindersController, SLOT(onRequestManagebleReminders()));
	connect(manageRemindersPage, SIGNAL(requestUpdateReminder(int,QString,QString,QString,int)),&remindersController, SLOT(onRequestUpdateReminder(int,QString,QString,QString,int)));
	connect(manageRemindersPage, SIGNAL(requestDeleteReminder(int)), &remindersController, SLOT(onRequestDeleteReminder(int)));

    //  --MainWindow signals connections
	connect(&mainWindow, SIGNAL(saveEverythingOnDisk()), &remindersController, SLOT(onSaveOnDisk()));
	connect(&mainWindow, SIGNAL(saveEverythingOnDisk()), &userController, SLOT(onSaveOnDisk()));
	mainWindow.show();
}


void ControllerMain::onUserLoggedIn() {
	ViewPageHome* homePage=static_cast<ViewPageHome*>(viewPages.value("Home"));
	mainWindow.setLoggedInView(userController.getCurrentUser());
	homePage->setLoggedInView(userController.getCurrentUser());
	remindersController.setCurrentUser(userController.getCurrentUser());
	mainWindow.changePage(homePage);
}

void ControllerMain::onMainWindowMenuActionClicked(QAction *pAction) {
    mainWindow.getHeader()->showMenu();
	if(pAction->text()=="Logout") {
		auto homePage=static_cast<ViewPageHome*>(mainWindow.getHomePage());
		mainWindow.setLoggedOutView();
		homePage->setLoggedOutView();
		mainWindow.changePage(homePage);
		if(mainWindow.getCurrentPage()==homePage)
			emit homePage->requestGeneralReminders();
	} else if(viewPages.contains(pAction->text()))
        mainWindow.changePage(viewPages.value(pAction->text()));
}


ControllerMain::~ControllerMain() {
    // I don't have to do nothing, because QMap is properly destroyed thanks to the
    // parenting hierarchy of viewpages (all of them have ViewMainWindow as parent)
}



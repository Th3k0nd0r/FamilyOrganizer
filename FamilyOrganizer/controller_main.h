#ifndef CONTROLLER_MAIN_H
#define CONTROLLER_MAIN_H

#include <view_mainwindow.h>
#include <QObject>
#include <controller_user.h>
#include <controller_reminders.h>

class ControllerMain : public QObject {

Q_OBJECT

private:
	ViewMainWindow mainWindow;
	QMap<QString, ViewPage*> viewPages;

	ControllerUser userController;
	ControllerReminders remindersController;

public:
	ControllerMain();
	void startApp();
	~ControllerMain();

public slots:
    void onUserLoggedIn();
	void onMainWindowMenuActionClicked(QAction* pAction);
};

#endif // CONTROLLER_MAIN_H

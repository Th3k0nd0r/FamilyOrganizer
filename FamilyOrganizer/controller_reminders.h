#ifndef CONTROLLER_REMINDERS_H
#define CONTROLLER_REMINDERS_H

#include <model_reminder.h>
#include <model_user.h>
#include <QObject>

class ControllerReminders : public QObject {

Q_OBJECT

private:
	ModelShowcase showcase;
	ModelUser* currentUser;

public:
	ControllerReminders(ModelUser* pCurrentUser = nullptr);
	void setCurrentUser(ModelUser* pCurrentUser);

signals:
	void onHomepageResponse(const QList<ModelReminder*>& pReminders) const;
	void onShowcaseUpdated(const QList<ModelReminder*>& reminders) const;

public slots:
    // For signals from buttons on HomePage
	void onRequestRemindersForHome() const;
	void onRequestRemindersForAll() const;
	void onRequestPrivateReminders() const;
	void onRequestRemindersForParents() const;
	void onRequestRemindersForChildren() const;
	void onRequestRemindersForGuests() const;
	void onRequestGeneralReminders() const;
    void onRequestSentReminders() const;
    void onFilterRemindersByCategory() const;

    // For signals from Form on New Reminder page
	void onNewReminderFormSubmitted();

    // For signals from ManageReminders page
    void onRequestManagebleReminders() const;
	void onRequestUpdateReminder(const int ID, const QString& title, const QString& description, const QString& category, const int target);
	void onRequestDeleteReminder(const int ID);

    // For saving data on disk after application close event
	void onSaveOnDisk();
};

#endif // CONTROLLER_REMINDERS_H

#include "controller_reminders.h"

#include <model_imagereminder.h>
#include <view_mainwindow.h>
#include <view_page_home.h>
#include <view_page_newreminder.h>
#include <QMessageBox>
#include <QDateTime>

ControllerReminders::ControllerReminders(ModelUser* pCurrentUser) :
	currentUser(pCurrentUser)
{
	showcase.readFromFile();
}

void ControllerReminders::setCurrentUser(ModelUser *pCurrentUser) {
	currentUser = pCurrentUser;
}



void ControllerReminders::onRequestPrivateReminders() const {
	auto privateReminders = showcase.getRemindersBySpecificTarget(currentUser->getUsername());
	emit onHomepageResponse(privateReminders);
}

void ControllerReminders::onRequestRemindersForAll() const {
	emit onHomepageResponse(showcase.getRemindersByTarget(ReminderTarget::AllUsers));
}

void ControllerReminders::onRequestRemindersForChildren() const {
	emit onHomepageResponse(showcase.getRemindersByTarget(ReminderTarget::ChildUser));
}

void ControllerReminders::onRequestRemindersForGuests() const {
	emit onHomepageResponse(showcase.getRemindersByTarget(ReminderTarget::GuestUser));
}

void ControllerReminders::onRequestRemindersForParents() const {
	emit onHomepageResponse(showcase.getRemindersByTarget(ReminderTarget::ParentUser));
}

void ControllerReminders::onRequestRemindersForHome() const {
	emit onHomepageResponse(currentUser->getRemindersForMe(showcase));
}

void ControllerReminders::onRequestGeneralReminders() const {
	emit onHomepageResponse(showcase.getRemindersByTarget(ReminderTarget::AllUsers));
}

void ControllerReminders::onFilterRemindersByCategory() const {
	auto a = qobject_cast<ViewPageHome*>(sender());
	if(!a)
		return;
	auto cv = a->getCurrentViewedReminders();
	if(cv.isEmpty())
		QMessageBox::information(a, "Errore",
								 "Non ci sono promemorie da filtrare, fare una ricerca diversa e riprovare.", QMessageBox::Ok);
	else
		emit onHomepageResponse(cv.values(a->getRequestedCategory()));
}

void ControllerReminders::onRequestSentReminders() const {
	emit onHomepageResponse(showcase.getRemindersByAuthor(currentUser->getUsername()));
}

void ControllerReminders::onNewReminderFormSubmitted() {
	auto a = qobject_cast<ViewPageNewReminder*>(sender());

	if(!a)
		return;
	if(a->getTitle().isEmpty() ||
	   a->getDescription().isEmpty() ||
			a->getCategory().isEmpty() ||
			(a->getTargetType()==1 && a->getSpecificTargetUsername().isEmpty()) ||
			(a->getReminderType()==1 && a->getImageUrl().isEmpty()))
		QMessageBox::information(a, "Errore",
								 "Compilare tutti i campi e riprovare.", QMessageBox::Ok);
	else {
		if(a->getReminderType()==0)
			showcase.addNewReminder(new ModelReminder(showcase.getLastID()+1,
												  a->getTitle(),
												  a->getDescription(),
												  a->getCategory(),
												  QDateTime::currentDateTime().toString(),
												  currentUser->getUsername(),
												  static_cast<ReminderTarget>(a->getTargetType()),
												  (a->getTargetType()==1 ? a->getSpecificTargetUsername() : "-")
												  ));
		 else
			showcase.addNewReminder(new ModelImageReminder(showcase.getLastID()+1,
												  a->getTitle(),
												  a->getDescription(),
												  a->getCategory(),
												  QDateTime::currentDateTime().toString(),
												  currentUser->getUsername(),
												  static_cast<ReminderTarget>(a->getTargetType()),
												  a->getImageUrl(),
												  (a->getTargetType()==1 ? a->getSpecificTargetUsername() : "-")
												  ));
		QMessageBox::information(a, "Successo", "Promemoria creato con successo!", QMessageBox::Ok);
	}
	emit onShowcaseUpdated(showcase.getAllReminders());
}

void ControllerReminders::onRequestManagebleReminders() const {
    if(currentUser->getTargetType() == ReminderTarget::ParentUser)
        emit onShowcaseUpdated(showcase.getAllReminders());
    else
        emit onShowcaseUpdated(showcase.getRemindersByAuthor(currentUser->getUsername()));
}

void ControllerReminders::onRequestUpdateReminder(const int ID, const QString &title, const QString &description, const QString &category, const int target) {
	auto reminderToUpdate = showcase.getReminderById(ID);
	if(!reminderToUpdate)
		return;

	reminderToUpdate->setTitle(title);
	reminderToUpdate->setDescription(description);
	reminderToUpdate->setCategory(category);
	reminderToUpdate->setTarget(static_cast<ReminderTarget>(target));
    onRequestManagebleReminders(); //this because the normal user can't edit all reminders.
}

void ControllerReminders::onRequestDeleteReminder(const int ID) {
	showcase.deleteReminder(ID);
    onRequestManagebleReminders();  //this because the normal user can't edit all reminders.
}

void ControllerReminders::onSaveOnDisk() {
	auto a = qobject_cast<ViewMainWindow*>(sender());

	if(!a)
		return;
	if(!showcase.saveToFile())
		QMessageBox::information(a, "Errore", "Impossibile salvare le promemorie su disco.", QMessageBox::Ok);

}

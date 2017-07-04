#ifndef SHOWCASE_H
#define SHOWCASE_H

#include <model.h>
#include <QList>
#include <model_reminder.h>


class ModelShowcase : public Model {

private:
	QList<ModelReminder*> reminders;
	int lastIDAdded;

public:
	ModelShowcase();
	void addNewReminder(ModelReminder* r);
	void deleteReminder(const int& ID);

	ModelReminder* getReminderById(const int& pID) const;
	QList<ModelReminder*> getRemindersByTarget(ReminderTarget pTarget) const;
	QList<ModelReminder*> getRemindersBySpecificTarget(const QString& pUsername) const;
	QList<ModelReminder*> getRemindersByCategory(const QString& pCategory) const;
	QList<ModelReminder*> getRemindersByAuthor(const QString& pUsername) const;
	QList<ModelReminder*> getBaseRemindersForUser(const QString& pUsername) const;
	QList<ModelReminder*> getAllReminders() const;
	int getLastID() const;

	//For storage
	virtual QString serialize() const override;
	virtual void deSerialize(const QString& data) override;

	~ModelShowcase(); //distruzione profonda
};

#endif // SHOWCASE_H

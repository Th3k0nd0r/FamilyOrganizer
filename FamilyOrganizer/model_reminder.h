#ifndef REMINDER_H
#define REMINDER_H

#include<QString>
#include<model_targettype.h>
#include <QXmlStreamReader>

class ModelReminder {

private:
	int ID;
	QString title;
	QString description;
	QString category;
	QString date;
	QString usernameAuthor;
	ReminderTarget target;
	QString usernameSpecificTarget;


public:
    const static QString ModelLabel;

	ModelReminder() = default;
	ModelReminder(int ID, const QString& pTitle, const QString& pDescription,
			  const QString& pCategory, const QString& date, const QString& pAuthor,
			  ReminderTarget pTarget, const QString& pUsernameSpecificTarget = "-");

	int getID() const;
	QString getTitle() const;
	QString getDescription() const;
	QString getCategory() const;
	QString getDate() const;
	QString getUsernameAuthor() const;
	ReminderTarget getTarget() const;
	QString getUsernameSpecificTarget() const;

	void setID(int pID);
	void setTitle(const QString& pTitle);
	void setDescription(const QString& pDescription);
	void setDate(const QString&);
	void setCategory(const QString& pCategory);
	void setAuthor(const QString& pAuthor);
	void setTarget(ReminderTarget pTarget);
	void setSpecificTarget(const QString& pUsername);

	virtual void serialize(QXmlStreamWriter&) const;
	virtual void deSerialize(QXmlStreamReader&);

	virtual ~ModelReminder() = default;

};

#endif // REMINDER_H

#ifndef USER_H
#define USER_H

#include <model_reminder.h>
#include <model_showcase.h>
#include <QFlags>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

class ModelUser {
public:
	enum Permission {
		CreateUsers = 1,
		CreateReminders = 2
	};
	Q_DECLARE_FLAGS(Permissions, Permission)

private:
	QString name;
	QString username;
	QString password;
	Permissions userPermissions;


public:
	static QString cryptPassword(const QString& data);
	ModelUser(const QString& pName, const QString& pUsername, const QString& pPassword, Permissions pUserPermissions);

	bool checkLogin(const QString& pPassword) const;




	Permissions getPermissions() const;
	QString getName() const;
	QString getUsername() const;
    QString getPassword() const;

    virtual QList<ModelReminder*> getRemindersForMe(const ModelShowcase& showcase) const;
    virtual void serialize(QXmlStreamWriter&) const;
    virtual void deSerialize(QXmlStreamReader&);
    virtual QString getModelLabel() const=0;
    virtual ReminderTarget getTargetType() const = 0;

	void setName(const QString& pName);
	void setUsername(const QString& pUsername);
	void setPassword(const QString& pPassword, const bool& alreadyCrypted = false);
	void setPermissions(Permissions pUserPermissions);

	virtual ~ModelUser();




};
Q_DECLARE_OPERATORS_FOR_FLAGS(ModelUser::Permissions)
#endif // USER_H

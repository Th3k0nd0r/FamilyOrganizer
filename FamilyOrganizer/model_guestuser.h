#ifndef GUESTUSER_H
#define GUESTUSER_H

#include <model_user.h>

class ModelGuestUser : public ModelUser {

public:
    const static QString ModelLabel;

	ModelGuestUser(const QString& pName="-", const QString& pUsername="-", const QString& pPassword="-",
				   ModelUser::Permissions pUserPermissions = 0);

	virtual ReminderTarget getTargetType() const override;
	virtual QString getModelLabel() const override;
	virtual QList<ModelReminder*> getRemindersForMe(const ModelShowcase& showcase) const override;

};

#endif // GUESTUSER_H

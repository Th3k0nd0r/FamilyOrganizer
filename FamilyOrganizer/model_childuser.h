#ifndef CHILDUSER_H
#define CHILDUSER_H

#include <model_user.h>

class ModelChildUser : public ModelUser {

public:
    const static QString ModelLabel;

	ModelChildUser(const QString& pName="-", const QString& pUsername="-", const QString& pPassword="-",
				   ModelUser::Permissions pUserPermissions = ModelUser::CreateReminders);

	virtual ReminderTarget getTargetType() const override;
	virtual QString getModelLabel() const override;
	virtual QList<ModelReminder*> getRemindersForMe(const ModelShowcase& showcase) const override;
};

#endif // CHILDUSER_H

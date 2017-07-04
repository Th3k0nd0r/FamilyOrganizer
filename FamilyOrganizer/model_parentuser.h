#ifndef PARENTUSER_H
#define PARENTUSER_H

#include <model_user.h>

class ModelParentUser : public ModelUser {

public:
    const static QString ModelLabel;

	ModelParentUser(const QString& pName="-", const QString& pUsername="-",
					const QString& pPassword="-",
					ModelUser::Permissions pUserPermissions = ModelUser::CreateReminders | ModelUser::CreateUsers);

	virtual ReminderTarget getTargetType() const override;
	virtual QString getModelLabel() const override;
	virtual QList<ModelReminder*> getRemindersForMe(const ModelShowcase& showcase) const override;
};

#endif // PARENTUSER_H

#include "model_childuser.h"

const QString ModelChildUser::ModelLabel = "ChildUser";
ModelChildUser::ModelChildUser(const QString& pName, const QString& pUsername, const QString& pPassword, ModelUser::Permissions pUserPermissions):
	ModelUser(pName, pUsername, pPassword, pUserPermissions) { }

QList<ModelReminder*> ModelChildUser::getRemindersForMe(const ModelShowcase &showcase) const {
	QList<ModelReminder*> baseReminders = showcase.getBaseRemindersForUser(getUsername());
	QList<ModelReminder*> thisTargetReminders = showcase.getRemindersByTarget(ReminderTarget::ChildUser);
	if(!thisTargetReminders.isEmpty())
		for(auto it=thisTargetReminders.constBegin(); it!=thisTargetReminders.end(); ++it)
			baseReminders.push_front(*it);
    return baseReminders;
}

ReminderTarget ModelChildUser::getTargetType() const {
	return ReminderTarget::ChildUser;
}
QString ModelChildUser::getModelLabel() const {
	return ModelLabel;
}

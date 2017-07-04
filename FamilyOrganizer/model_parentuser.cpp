#include "model_parentuser.h"
#include <iostream>
const QString ModelParentUser::ModelLabel = "ParentUser";
ModelParentUser::ModelParentUser(const QString& pName, const QString& pUsername, const QString& pPassword, ModelUser::Permissions pUserPermissions):
	ModelUser(pName, pUsername, pPassword, pUserPermissions) { }

QList<ModelReminder*> ModelParentUser::getRemindersForMe(const ModelShowcase& showcase) const {
	auto baseReminders = showcase.getBaseRemindersForUser(getUsername());
	auto thisTargetReminders = showcase.getRemindersByTarget(ReminderTarget::ParentUser);
	if(!thisTargetReminders.isEmpty()) {

		for(auto it=thisTargetReminders.constBegin(); it!=thisTargetReminders.end(); ++it)
			baseReminders.push_front(*it);
	}
	return baseReminders;
}

ReminderTarget ModelParentUser::getTargetType() const {
	return ReminderTarget::ParentUser;
}

QString ModelParentUser::getModelLabel() const {
	return ModelLabel;
}

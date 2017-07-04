#include "model_guestuser.h"

const QString ModelGuestUser::ModelLabel = "GuestUser";
ModelGuestUser::ModelGuestUser(const QString& pName, const QString& pUsername, const QString& pPassword, ModelUser::Permissions pUserPermissions):
	ModelUser(pName, pUsername, pPassword, pUserPermissions) { }

QList<ModelReminder*> ModelGuestUser::getRemindersForMe(const ModelShowcase &showcase) const {
	auto baseReminders = showcase.getBaseRemindersForUser(getUsername());
	auto thisTargetReminders = showcase.getRemindersByTarget(ReminderTarget::GuestUser);

	if(!thisTargetReminders.isEmpty())
		for(auto it=thisTargetReminders.constBegin(); it!=thisTargetReminders.end(); ++it)
			baseReminders.push_front(*it);
	return baseReminders;

}

ReminderTarget ModelGuestUser::getTargetType() const {
	return ReminderTarget::GuestUser;
}

QString ModelGuestUser::getModelLabel() const {
	return ModelLabel;
}

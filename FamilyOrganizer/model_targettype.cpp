#include <model_targettype.h>

QString ModelTargetType::targetToString(ReminderTarget pTarget) {
	switch(pTarget) {
	case ReminderTarget::AllUsers :
		return "Tutti";
	case ReminderTarget::SpecificUser :
		return "Privato";
	case ReminderTarget::ParentUser :
		return "Genitori";
	case ReminderTarget::ChildUser :
		return "Figli";
	case ReminderTarget::GuestUser :
		return "Ospiti";
	}
	return "Indefinito";
}

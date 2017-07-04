#ifndef MODELTARGETTYPE_H
#define MODELTARGETTYPE_H

#include <QString>

class ModelTargetType {

public:
	enum PossibleTarget {

		//Target Modes
		AllUsers,
		SpecificUser,

        //Target user subtypes
		ParentUser,
		ChildUser,
		GuestUser
	};

	typedef ModelTargetType::PossibleTarget ReminderTarget;

	static QString targetToString(ReminderTarget pTarget);
};


typedef ModelTargetType::PossibleTarget ReminderTarget;
#endif

#include "view_page_manageusers.h"
#include <view_singleuserrow.h>
#include <model_parentuser.h>
#include <model_childuser.h>
#include <model_guestuser.h>

ViewPageManageUsers::ViewPageManageUsers(QWidget* parent):
	ViewPage("Gestione utenti", parent),
	layout(new QVBoxLayout(this)),
	scrollArea(new QScrollArea(this)),
	listContainer(new QWidget(scrollArea)),
	listLayout(new QGridLayout(listContainer)),
	nameLabel(new QLabel("Nome", this)),
	userLabel(new QLabel("Username", this)),
	passLabel(new QLabel("Password", this)),
	userTypeLabel(new QLabel("Tipo", this)),
	permissionsLabel(new QLabel("Permessi", this))

{
	scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	scrollArea->setWidgetResizable(true);
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scrollArea->setStyleSheet("QScrollArea {border: 0px;}");

	listContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	listLayout->addWidget(nameLabel, 0, 0, Qt::AlignHCenter);
	listLayout->addWidget(userLabel, 0, 1, Qt::AlignHCenter);
	listLayout->addWidget(passLabel, 0, 2, Qt::AlignHCenter);
	listLayout->addWidget(userTypeLabel, 0, 3, Qt::AlignHCenter);
	listLayout->addWidget(permissionsLabel, 0, 4, Qt::AlignHCenter);

	listContainer->setLayout(listLayout);

	scrollArea->setWidget(listContainer);
	layout->addWidget(scrollArea);
	layout->setSpacing(0);
	layout->setMargin(0);
	setLayout(layout);

	setStyleSheet("QLabel { font-size: 18px; color:black; } ");
	hide();
}



void ViewPageManageUsers::loadUsers(const QMap<QString, ModelUser*>& users) {
	int clearFrom = listLayout->count()>5 ? 6 : 0;
	clearLayout(listLayout, clearFrom);

	int curRow=1;
	for(auto it = users.cbegin(); it!=users.cend(); ++it) {

		auto singleRow = new ViewSingleUserRow(*it, (*it)->getTargetType()-2, listContainer);
		connect(singleRow, SIGNAL(updateUserClicked()), this, SLOT(onUpdateUserClicked()));
		connect(singleRow, SIGNAL(deleteUserClicked()), this, SLOT(onDeleteUserClicked()));

		// this sets singlerow on the gridlayout
		singleRow->insertIntoGridLayout(listLayout, curRow);
		curRow++;
	}
	if(curRow==1) {
		clearLayout(listLayout);
		auto lab = new QLabel("Non ci sono utenti da gestire.", listContainer);
		lab->setAlignment(Qt::AlignHCenter);
		listLayout->addWidget(lab);
	}
	listContainer->adjustSize();
}

void ViewPageManageUsers::showEvent(QShowEvent *event) {
	emit requestAllUsers();

    (void)event; //silent warning unused parameter
}

void ViewPageManageUsers::onUpdateUserClicked() const {
	auto a = qobject_cast<ViewSingleUserRow*>(sender());
	if(!a)
		return;
	emit requestUpdateUser(a->getName(), a->getUsername(), a->getUserType(), a->getPermissions());
}

void ViewPageManageUsers::onDeleteUserClicked() const {
	auto a = qobject_cast<ViewSingleUserRow*>(sender());
	if(!a)
		return;
	emit requestDeleteUser(a->getUsername());
}

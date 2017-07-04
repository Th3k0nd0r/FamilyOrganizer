#include "view_page_home.h"
#include <view_reminder.h>
#include <iostream>
#include <model_imagereminder.h>
#include <model_parentuser.h>
#include <model_childuser.h>
#include <model_guestuser.h>

ViewPageHome::ViewPageHome(QWidget* parent) :
	ViewPage("BACHECA", parent),
	scrollArea(new QScrollArea(this)),
	layout(new QVBoxLayout(this)),

	remindersContainer(new QFrame(scrollArea)),
	remindersLayout(new QHBoxLayout(remindersContainer)),

	loggedInMenu(new QWidget(this)),
	loggedInMenuLayout(new QHBoxLayout(loggedInMenu)),

	currentSelectedButton(0),

	categoryEdit(new QLineEdit("Categoria", loggedInMenu)),
	remindersByCategoryButton(new QPushButton("Filtra", loggedInMenu))
{

	loggedInMenuLayout->setSpacing(0);
	loggedInMenuLayout->setMargin(0);

    // setting buttons in the array
	searchButtons[0] = new QPushButton("Home", loggedInMenu);
	searchButtons[1] = new QPushButton("Per Tutti", loggedInMenu);
	searchButtons[2] = new QPushButton("Per Genitori", loggedInMenu);
	searchButtons[3] = new QPushButton("Per Figli", loggedInMenu);
	searchButtons[4] = new QPushButton("Per Ospiti", loggedInMenu);
	searchButtons[5] = new QPushButton("Per Me", loggedInMenu);
	searchButtons[6] = new QPushButton("Inviati", loggedInMenu);

    // adding widgets to the loggedinmenu
	for(int i=0; i<7; ++i) {
		//adding the search button to the loggedinmenu (menu that appears only when user is logged in
		loggedInMenuLayout->addWidget(searchButtons[i]);

		//setting custom style (requestButton class) for the searchButton
		searchButtons[i]->setProperty("requestButton", true);
		searchButtons[i]->setCursor(Qt::PointingHandCursor);
		//connect the searchbutton to setSelectedButton in order to make it change style on selected
		connect(searchButtons[i], SIGNAL(clicked(bool)), this, SLOT(setSelectedButton()));
	}

	//connecting clicked signals of buttons to custom slots
	connect(searchButtons[0], SIGNAL(clicked(bool)), this, SIGNAL(requestRemindersForHome()));
	connect(searchButtons[1], SIGNAL(clicked(bool)), this, SIGNAL(requestRemindersForAll()));
	connect(searchButtons[2], SIGNAL(clicked(bool)), this, SIGNAL(requestRemindersForParents()));
	connect(searchButtons[3], SIGNAL(clicked(bool)), this, SIGNAL(requestRemindersForChildren()));
	connect(searchButtons[4], SIGNAL(clicked(bool)), this, SIGNAL(requestRemindersForGuests()));
	connect(searchButtons[5], SIGNAL(clicked(bool)), this, SIGNAL(requestPrivateReminders()));
	connect(searchButtons[6], SIGNAL(clicked(bool)), this, SIGNAL(requestSentReminders()));

	connect(remindersByCategoryButton, SIGNAL(clicked(bool)), this, SIGNAL(requestFilterRemindersByCategory()));

	loggedInMenuLayout->addWidget(categoryEdit);
	loggedInMenuLayout->addWidget(remindersByCategoryButton);
	loggedInMenu->setLayout(loggedInMenuLayout);


	categoryEdit->setProperty("requestButton", true);
	remindersByCategoryButton->setProperty("requestButton", true);
	categoryEdit->setMaximumWidth(250);
	remindersByCategoryButton->setMaximumWidth(100);
	remindersByCategoryButton->setCursor(Qt::PointingHandCursor);


	setStyleSheet("*[requestButton=\"true\"] { border:0px; }"
				  "*[selectedButton=\"true\"] {background-color: #00355e;} ");

	searchButtons[0]->setProperty("selectedButton", true);
	currentSelectedButton=searchButtons[0];

	loggedInMenu->hide();

	for(int i=0; i<2; ++i) {
		remindersColumnsContainer[i] = new QWidget(scrollArea);
		remindersColumnsLayout[i] = new QVBoxLayout(remindersColumnsContainer[i]);
		remindersColumnsContainer[i]->setLayout(remindersColumnsLayout[i]);
		remindersLayout->addWidget(remindersColumnsContainer[i], 0, Qt::AlignTop);
	}
	remindersContainer->setLayout(remindersLayout);
	remindersContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	scrollArea->setWidgetResizable(true);
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scrollArea->setWidget(remindersContainer);
	scrollArea->setStyleSheet("QScrollArea {border: 0px;}");


	layout->setSpacing(0);
	layout->setMargin(0);
	layout->addWidget(loggedInMenu);
	layout->addWidget(scrollArea);
	setLayout(layout);

}


void ViewPageHome::loadReminders(const QList<ModelReminder*>& pReminders) {
	clearLayout(remindersColumnsLayout[0]);
	clearLayout(remindersColumnsLayout[1]);
	currentViewedReminders.clear();


	int column=0;
	for(auto it = pReminders.cbegin(); it!=pReminders.cend(); ++it) {
		currentViewedReminders.insertMulti((*it)->getCategory(), *it);
		remindersColumnsLayout[column]->addWidget(new ViewReminder(*it, remindersColumnsContainer[column]), 0, Qt::AlignHCenter);
		remindersColumnsContainer[column]->adjustSize();
		if(column==1)
			column=0;
		else
			column++;
	}
	if(pReminders.isEmpty()) {
		QLabel* lab[2] = {new QLabel("Non ci sono promemorie da visualizzare.", remindersContainer),
						  new QLabel("Non ci sono promemorie da visualizzare.", remindersContainer)};
		lab[0]->setAlignment(Qt::AlignHCenter);
		lab[1]->setAlignment(Qt::AlignHCenter);
		remindersColumnsLayout[0]->addWidget(lab[0]);
		remindersColumnsLayout[1]->addWidget(lab[1]);
	}
	remindersContainer->adjustSize();
}



void ViewPageHome::setLoggedInView(ModelUser* currentUser) {
	for(int i=2; i<5; i++)
		searchButtons[i]->hide();
	searchButtons[currentUser->getTargetType()]->show(); //gettargettype returns int x 2<=x<=4
	loggedInMenu->show();
}

void ViewPageHome::setLoggedOutView() {

	loggedInMenu->hide();
}

void ViewPageHome::setSelectedButton() {
	auto a = qobject_cast<QPushButton*>(sender());
	if(!a)
		return;
	currentSelectedButton->setProperty("selectedButton", false);
	currentSelectedButton = a;
	a->setProperty("selectedButton", true);
	setStyleSheet("*[requestButton=\"true\"] { border:0px; }"
				  "*[selectedButton=\"true\"] {background-color: #00355e;} ");
}

QString ViewPageHome::getRequestedCategory() const {
	return categoryEdit->text();
}

const QMultiMap<QString, ModelReminder*>& ViewPageHome::getCurrentViewedReminders() const {
	return currentViewedReminders;
}

void ViewPageHome::showEvent(QShowEvent *event) {
	for(int i=0; i<7; ++i)
		searchButtons[i]->setProperty("selectedButton", false);
	searchButtons[0]->setProperty("selectedButton", true);
	currentSelectedButton=searchButtons[0];
	setStyleSheet("*[requestButton=\"true\"] { border:0px; }"
				  "*[selectedButton=\"true\"] {background-color: #00355e;} ");
	if(loggedInMenu->isVisible())
		emit requestRemindersForHome();
	else
		emit requestGeneralReminders();

    (void)event; //silent warning unused parameter
}

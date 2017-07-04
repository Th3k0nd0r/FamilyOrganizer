#include "view_page_managereminders.h"
#include <iostream>
#include <view_singlereminderrow.h>
#include <QLabel>

ViewPageManageReminders::ViewPageManageReminders(QWidget* parent):
	ViewPage("Gestione promemorie", parent),
	layout(new QVBoxLayout(this)),
	scrollArea(new QScrollArea(this)),
	listContainer(new QWidget(scrollArea)),
    listLayout(new QGridLayout(listContainer))
{

	scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	scrollArea->setWidgetResizable(true);
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scrollArea->setStyleSheet("QScrollArea {border: 0px;}");

	listContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    listLayout->addWidget(new QLabel("ID", listContainer), 0, 0,Qt::AlignHCenter);
    listLayout->addWidget(new QLabel("Titolo", listContainer), 0, 1,Qt::AlignHCenter);
    listLayout->addWidget(new QLabel("Descrizione", listContainer), 0, 2,Qt::AlignHCenter);
    listLayout->addWidget(new QLabel("Categoria", listContainer), 0, 3,Qt::AlignHCenter);
    listLayout->addWidget(new QLabel("Autore", listContainer), 0, 4,Qt::AlignHCenter);
    listLayout->addWidget(new QLabel("Destinazione", listContainer), 0, 5,Qt::AlignHCenter);
    listLayout->addWidget(new QLabel("Dest. priv.", listContainer), 0, 6,Qt::AlignHCenter);
	listContainer->setLayout(listLayout);
	scrollArea->setWidget(listContainer);
	layout->addWidget(scrollArea);
	layout->setSpacing(0);
	layout->setMargin(0);
	setLayout(layout);

	setStyleSheet("QLabel { font-size: 18px; color:black; } ");

	hide();
}

void ViewPageManageReminders::loadReminders(const QList<ModelReminder*> &reminders) {
    int clearFrom = 0;
	clearLayout(listLayout, clearFrom); //destroys all widgets inside reminderslayout

    /* HEADING destroyed with clearLayout function or in the end with the parent listContainer. So we gotta re-add it*/
    listLayout->addWidget(new QLabel("ID", listContainer), 0, 0,Qt::AlignHCenter);
    listLayout->addWidget(new QLabel("Titolo", listContainer), 0, 1,Qt::AlignHCenter);
    listLayout->addWidget(new QLabel("Descrizione", listContainer), 0, 2,Qt::AlignHCenter);
    listLayout->addWidget(new QLabel("Categoria", listContainer), 0, 3,Qt::AlignHCenter);
    listLayout->addWidget(new QLabel("Autore", listContainer), 0, 4,Qt::AlignHCenter);
    listLayout->addWidget(new QLabel("Destinazione", listContainer), 0, 5,Qt::AlignHCenter);
    listLayout->addWidget(new QLabel("Dest. priv.", listContainer), 0, 6,Qt::AlignHCenter);
    /* END HEADING */

	int curRow=1;
	for(auto it = reminders.cbegin(); it!=reminders.cend(); ++it) {
		auto singleRow = new ViewSingleReminderRow(*it, listContainer);
		connect(singleRow, SIGNAL(updateReminderClicked()), this, SLOT(onUpdateReminderClicked()));
		connect(singleRow, SIGNAL(deleteReminderClicked()), this, SLOT(onDeleteReminderClicked()));
		// this sets singlerow on the gridlayout
		singleRow->insertIntoGridLayout(listLayout, curRow);
		curRow++;
	}
	if(curRow==1) {
		clearLayout(listLayout);
        auto lab = new QLabel("Non ci sono promemorie da gestire.", listContainer); //destroyed with clearLayout function or in the end with the parent.
        lab->setAlignment(Qt::AlignHCenter);
		listLayout->addWidget(lab);
	}
	listContainer->adjustSize();
}

void ViewPageManageReminders::showEvent(QShowEvent *event) {
    emit requestManagebleReminders();

    (void)event; //silent warning unused parameter
}

void ViewPageManageReminders::onUpdateReminderClicked() const {
	auto a = qobject_cast<ViewSingleReminderRow*>(sender());
	if(!a)
		return;
	emit requestUpdateReminder(a->getID(), a->getTitle(), a->getDescription(), a->getCategory(), a->getTarget());
}

void ViewPageManageReminders::onDeleteReminderClicked() const {
	auto a = qobject_cast<ViewSingleReminderRow*>(sender());
	if(!a)
		return;
	emit requestDeleteReminder(a->getID());
}




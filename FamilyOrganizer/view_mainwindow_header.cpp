#include "view_mainwindow_header.h"

#include <QCoreApplication>
#include <QStyle>
#include <QStyleOption>
#include <QPainter>
#include <iostream>

const int ViewMainWindowHeader::MENU_WIDTH = 210;

ViewMainWindowHeader::ViewMainWindowHeader(QWidget* parent):
	View(parent),
	usernameLabel(new QLabel("", this)),
	titleLabel(new QLabel("FamilyOrganizer - Bacheca", this)),
	layout(new QHBoxLayout(this)),
	menuButton(new QPushButton(this)),
	menu(new QMenu(this)),
    menuActions(new QActionGroup(menu)),
    menuAnimation1(new QPropertyAnimation(menu, "minimumWidth")),
    menuAnimation2(new QPropertyAnimation(menu, "maximumWidth")),
    menuToggle(false),

	textColor("white")
{

	menu->addAction("Home");
	menu->addAction("Login");
    menu->setMinimumWidth(MENU_WIDTH);
	menu->setCursor(Qt::PointingHandCursor);
	menu->hide();
	foreach (QAction* a, menu->actions())
		menuActions->addAction(a);
	connect(menuActions, SIGNAL(triggered(QAction*)), this, SIGNAL(mainMenuActionClicked(QAction*)));


	//menuButton->setMenu(menu);
	menuButton->setFlat(false);
	menuButton->setStyleSheet("QPushButton{background-color: rgba(0,0,0,0); margin-left: 0px; border: 0px; background-image: url("+QCoreApplication::applicationDirPath()+"/data/menu-icon.png);}QPushButton::menu-indicator{image:url(none.jpg);}");
    connect(menuButton, SIGNAL(clicked(bool)), this, SLOT(showMenu()));


	menuButton->setCursor(Qt::PointingHandCursor);
	menuButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	menuButton->setMaximumSize(33,18);

    menuAnimation1->setDuration(200);
    menuAnimation1->setEndValue(MENU_WIDTH);//set minimumwidth to 200
    menuAnimation2->setDuration(200);
    menuAnimation2->setEndValue(0);//set maximumwidth to 0

	usernameLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	usernameLabel->setStyleSheet(" color: "+textColor+"; font-size: 25px;");
	usernameLabel->hide();

	titleLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	titleLabel->setStyleSheet("font-weight: 300; color: "+textColor+"; font-size: 30px; margin-left: -50px");
	titleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	titleLabel->setMinimumHeight(72);

	setObjectName("MainWindowHeader");
    setStyleSheet("#MainWindowHeader {background-color: #1c1c29; color: "+textColor+";}"
                  );
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	layout->addWidget(menuButton);
	layout->addWidget(usernameLabel);
	layout->addWidget(titleLabel);
	setLayout(layout);
}



void ViewMainWindowHeader::setTitle(const QString& pTitle) {
	titleLabel->setText(pTitle);
}

QMenu* ViewMainWindowHeader::getMenu() const {
	return menu;
}

void ViewMainWindowHeader::setLoggedInView(ModelUser* currentUser) {

	auto userPermissions = currentUser->getPermissions();
	usernameLabel->setText(currentUser->getUsername());
	usernameLabel->show();
	titleLabel->setStyleSheet("font-weight: 300; color: "+textColor+"; font-size: 30px; margin-left: -"+QString::fromStdString(std::to_string(usernameLabel->width()+menuButton->width()))+"px;");

	menu->clear();

	menu->addAction("Home");
	if(userPermissions.testFlag(ModelUser::CreateUsers)) {
		menu->addAction("Nuovo utente");
		menu->addAction("Gestione utenti");
	}
	if(userPermissions.testFlag(ModelUser::CreateReminders)) {
		menu->addAction("Nuovo promemoria");
		menu->addAction("Gestione promemorie");
	}

	menu->addAction("Logout");
	updateMenuActions();

}
void ViewMainWindowHeader::setLoggedOutView() {

	usernameLabel->hide();
	menu->clear();
	menu->addAction("Home");
	menu->addAction("Login");
	titleLabel->setStyleSheet("font-weight: 300; color: "+textColor+"; font-size: 30px; margin-left: -"+QString::fromStdString(std::to_string(menuButton->width()))+"px;");
	updateMenuActions();
}

void ViewMainWindowHeader::updateMenuActions() {
	//need to update menuActions
	foreach(QAction* a, menuActions->actions()) {
		menuActions->removeAction(a);
		delete a;
	}
	foreach (QAction* a, menu->actions())
		menuActions->addAction(a);
}

void ViewMainWindowHeader::paintEvent(QPaintEvent *pe) {
  QStyleOption o;
  o.initFrom(this);
  QPainter p(this);
  style()->drawPrimitive(
	QStyle::PE_Widget, &o, &p, this);
  (void)pe; //silent warning unused parameter
}

void ViewMainWindowHeader::showMenu() {
    menu->setMaximumWidth(MENU_WIDTH);
    menu->setMinimumWidth(0);
    //menu->show();
    if(!menuToggle) {
        //show menu
        menu->setMaximumWidth(0);
        menu->show();
        menuAnimation1->start();
        menuToggle=true;
    } else {
        //hide menu
        menu->setMinimumWidth(MENU_WIDTH);
        menuAnimation2->start();
        menu->hide();
        menuToggle=false;
    }
}

#include "view_mainwindow.h"
#include <view_page_home.h>
#include <QStyle>
#include <QApplication>
#include <QDesktopWidget>

ViewMainWindow::ViewMainWindow(ViewPage* pHomePage, QWidget* parent):
	View(parent),
	mainLayout(new QVBoxLayout(this)),
	contentContainer(new QWidget(this)),
	contentLayout(new QHBoxLayout(contentContainer)),
    header(new ViewMainWindowHeader(this)),
	currentPage(pHomePage),
	homePage(pHomePage)
{

    header->setTitle(currentPage->getPageTitle());



	setObjectName("MainWindow");
    setStyleSheet("MainWindow {font-family: Segoe UI; font-weight: 300; } "
				  "MainWindow:focus {font-family: Segoe UI; font-weight: 300;border: none; outline: none;}"
                  "QLineEdit { font-family: Segoe UI; padding: 4px 8px; height: 35px; border:1px solid grey; min-height: 32px; font-size: 16px; } "
                  "QPushButton {font-family: Segoe UI; padding: 12px 20px; font-size: 16px; background-color: #00648f; border: 0px; color: white; } "
				  "QPushButton:hover {background-color: white; border: 1px solid #0078d7; color: #0078d7; } QLabel {font-size: 16px; }"
                  "QComboBox {font-family: Segoe UI; padding: 10px; font-size: 16px; }"
				  "QPushButton:focus {border: none; outline: none; }"
                  "QMenu {font-family: Segoe UI; background-color: #191817; font-size: 15px; border: 0px; } "
                  "QMenu::item {font-family: Segoe UI; background-color: transparent; color:white; padding: 20px; } "
                  "QMenu::item:selected {background-color: white; color: #191817; }");

	contentLayout->addWidget(header->getMenu());
	contentLayout->addWidget(currentPage);
	contentLayout->setSpacing(0);
	contentLayout->setMargin(0);
	mainLayout->setSpacing(0);
	mainLayout->setMargin(0);
	mainLayout->addWidget(header);
	mainLayout->addWidget(contentContainer);
	setLayout(mainLayout);

    setMinimumWidth(1100); setMinimumHeight(600);
    setGeometry(
                QStyle::alignedRect(
                    Qt::LeftToRight,
                    Qt::AlignCenter,
                    size(),
                    static_cast<QApplication *>(QApplication::instance())->desktop()->availableGeometry()
                )
            );
}

ViewPage* ViewMainWindow::getCurrentPage() const {
	return currentPage;
}

ViewMainWindowHeader* ViewMainWindow::getHeader() const {
	return header;
}

void ViewMainWindow::changePage(ViewPage* newPage) {
	if(currentPage == newPage || !currentPage)
		return;

	currentPage->hide();
    contentLayout->takeAt(1);
    contentLayout->addWidget(newPage);

	currentPage = newPage;
	newPage->show();
    header->setTitle(currentPage->getPageTitle());
}

ViewPage* ViewMainWindow::getHomePage() const {
	return homePage;
}
void ViewMainWindow::setLoggedInView(ModelUser* currentUser) {
	header->setLoggedInView(currentUser);
}
void ViewMainWindow::setLoggedOutView() {
	header->setLoggedOutView();
}

void ViewMainWindow::closeEvent(QCloseEvent *event) {
	emit saveEverythingOnDisk();

    (void)event; //silent warning unused parameter
}

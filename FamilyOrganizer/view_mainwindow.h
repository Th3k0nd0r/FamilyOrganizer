#ifndef VIEW_MAINWINDOW_H
#define VIEW_MAINWINDOW_H

#include <QVBoxLayout>

#include <view_mainwindow_header.h>
#include <view_page.h>
#include <view.h>
#include <model_user.h>

class ViewMainWindow : public View {
Q_OBJECT

private:
	QVBoxLayout* mainLayout;
	QWidget* contentContainer;
	QHBoxLayout* contentLayout;

    ViewMainWindowHeader* header;
	ViewPage* currentPage;
	ViewPage* homePage;

protected:
	void closeEvent(QCloseEvent *event) override; //override needed for serialization

public:
	ViewMainWindow(ViewPage* pHomePage, QWidget* parent = 0);


    void changePage(ViewPage* newPage);
	ViewMainWindowHeader* getHeader() const;
	ViewPage* getCurrentPage() const;
	ViewPage* getHomePage() const;
	void setLoggedInView(ModelUser* currentUser);
	void setLoggedOutView();

    //~ViewMainWindow();

signals:
	void saveEverythingOnDisk() const;
};

#endif // VIEW_MAINWINDOW_H

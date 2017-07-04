#ifndef VIEW_PAGE_HOME_H
#define VIEW_PAGE_HOME_H

#include <view_page.h>
#include <QGridLayout>
#include <QLabel>
#include <QScrollArea>
#include <QPushButton>
#include <QLineEdit>
#include <model_reminder.h>

class ViewPageHome : public ViewPage {

Q_OBJECT

private:
	QScrollArea* scrollArea;
	QVBoxLayout* layout;

	QFrame* remindersContainer;
	QHBoxLayout* remindersLayout;

	QWidget* remindersColumnsContainer[2]; //using arrays in order to make possible the increment of number of columns. Not using
											//QGridlayout because it's not possible to set different Cell sizes
	QVBoxLayout* remindersColumnsLayout[2];

	QWidget* loggedInMenu;
	QHBoxLayout* loggedInMenuLayout;


	QPushButton* searchButtons[7];
	QPushButton* currentSelectedButton;
	QLineEdit* categoryEdit;
	QPushButton* remindersByCategoryButton;

    QMultiMap<QString, ModelReminder*> currentViewedReminders; //use of QMultiMap in order to ease the category filter

public:
	ViewPageHome(QWidget* parent=0);

	QString getRequestedCategory() const;
	const QMultiMap<QString, ModelReminder*>& getCurrentViewedReminders() const;

	void setLoggedInView(ModelUser* currentUser);
	void setLoggedOutView();
	void showEvent(QShowEvent *event) override;


private slots:
	void setSelectedButton();

public slots:
	void loadReminders(const QList<ModelReminder*>& pReminders);

signals:
	void requestRemindersForHome() const;
	void requestRemindersForAll() const;
	void requestRemindersForParents() const;
	void requestRemindersForChildren() const;
	void requestRemindersForGuests() const;
	void requestPrivateReminders() const;
	void requestGeneralReminders() const;
	void requestFilterRemindersByCategory() const;
	void requestSentReminders() const;


};

#endif // VIEW_PAGE_HOME_H

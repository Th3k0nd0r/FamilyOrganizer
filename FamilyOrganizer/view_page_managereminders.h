#ifndef VIEW_PAGE_MANAGEREMINDERS_H
#define VIEW_PAGE_MANAGEREMINDERS_H

#include <view_page.h>
#include <QLineEdit>
#include <QFormLayout>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QScrollArea>

class ViewPageManageReminders : public ViewPage {
Q_OBJECT

private:
	QVBoxLayout* layout;
	QScrollArea* scrollArea;
	QWidget* listContainer;
    QGridLayout* listLayout;


public:
	ViewPageManageReminders(QWidget* parent=0);
	void showEvent(QShowEvent *event) override;

private slots:
	void onUpdateReminderClicked() const;
	void onDeleteReminderClicked() const;

public slots:
	void loadReminders(const QList<ModelReminder*>& reminders);

signals:
    void requestManagebleReminders() const;
	void requestUpdateReminder(const int ID, const QString& title, const QString& description, const QString& category, const int target) const;
	void requestDeleteReminder(const int ID) const;

};

#endif // VIEW_PAGE_MANAGEREMINDERS_H

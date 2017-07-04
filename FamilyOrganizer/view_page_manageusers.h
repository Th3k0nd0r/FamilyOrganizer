#ifndef VIEW_PAGE_MANAGEUSERS_H
#define VIEW_PAGE_MANAGEUSERS_H

#include <view_page.h>
#include <QFormLayout>
#include <QLabel>
#include <QScrollArea>

class ViewPageManageUsers : public ViewPage {

Q_OBJECT

private:
	QVBoxLayout* layout;
	QScrollArea* scrollArea;
	QWidget* listContainer;
	QGridLayout* listLayout;

	QLabel* nameLabel;
	QLabel* userLabel;
	QLabel* passLabel;
	QLabel* userTypeLabel;
	QLabel* permissionsLabel;

public:
	ViewPageManageUsers(QWidget* parent=0);
	void showEvent(QShowEvent *event) override;

private slots:
	void onUpdateUserClicked() const;
	void onDeleteUserClicked() const;

public slots:
	void loadUsers(const QMap<QString, ModelUser *>& users);

signals:
	void requestAllUsers() const;
	void requestUpdateUser(const QString& name, const QString& user, const int userType, ModelUser::Permissions pUserPermissions) const;
	void requestDeleteUser(const QString& username) const;
};

#endif // VIEW_PAGE_MANAGEUSERS_H

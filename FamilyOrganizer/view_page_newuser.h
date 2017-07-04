#ifndef VIEW_PAGE_NEWUSER_H
#define VIEW_PAGE_NEWUSER_H

#include <view_page.h>
#include <QLineEdit>
#include <QFormLayout>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>

class ViewPageNewUser : public ViewPage {

Q_OBJECT

private:
	QVBoxLayout* layout;

	QWidget* formContainer;
	QFormLayout* formLayout;
	QLineEdit* nameEdit;
	QLineEdit* userEdit;
	QLineEdit* passEdit;
	QCheckBox* createUsersPermissionCheck;
	QCheckBox* createRemindersPermissionCheck;
	QComboBox* userTypeCombo;
	QPushButton* submitButton;

public:
	ViewPageNewUser(QWidget* parent=0);
	QString getName() const;
	QString getUsername() const;
	QString getPassword() const;
	bool hasCreateUsersPermission() const;
	bool hasCreateRemindersPermission() const;
	int getUserType() const;

signals:
	void formSubmitted() const;
};

#endif // VIEW_PAGE_NEWUSER_H

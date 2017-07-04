#ifndef VIEW_PAGE_LOGIN_H
#define VIEW_PAGE_LOGIN_H

#include <view_page.h>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

class ViewPageLogin : public ViewPage {

Q_OBJECT

private:
	QVBoxLayout* layout;

	QWidget* formContainer;
	QFormLayout* formLayout;
	QLineEdit* userEdit;
	QLineEdit* passEdit;
	QPushButton* submitButton;

public:
	ViewPageLogin(QWidget* parent = 0);
	QString getUsername() const;
	QString getPassword() const;

signals:
	void formSubmitted() const;
};

#endif // VIEW_PAGE_LOGIN_H

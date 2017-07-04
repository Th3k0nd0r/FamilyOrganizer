#include "view_page_login.h"

ViewPageLogin::ViewPageLogin(QWidget* parent) :
	ViewPage("Accedi al tuo account", parent),
	layout(new QVBoxLayout(this)),
	formContainer(new QWidget(this)),
	formLayout(new QFormLayout(formContainer)),
	userEdit(new QLineEdit(formContainer)),
	passEdit(new QLineEdit(formContainer)),
	submitButton(new QPushButton("Accedi", formContainer))
{


	passEdit->setEchoMode(QLineEdit::Password);
	connect(submitButton, SIGNAL(clicked(bool)), this, SIGNAL(formSubmitted()));

	formLayout->setFormAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
	formLayout->setLabelAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
	//formLayout->setVerticalSpacing(20);
	auto lab = new QLabel("Username: ", formContainer);
	lab->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
	auto lab2 = new QLabel("Password: ", formContainer);
	lab2->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
	formLayout->addRow(lab, userEdit);
	formLayout->addRow(lab2, passEdit);
	formLayout->addRow(submitButton);
	submitButton->setCursor(Qt::PointingHandCursor);
	userEdit->setText("Marco");
	passEdit->setText("password");

    formContainer->setLayout(formLayout);
	formContainer->setMinimumWidth(300);
	formContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	layout->setContentsMargins(200,0,200,0);
	layout->addWidget(formContainer);
	setLayout(layout);
}

QString ViewPageLogin::getUsername() const {
	return userEdit->text();
}

QString ViewPageLogin::getPassword() const {
	return passEdit->text();
}

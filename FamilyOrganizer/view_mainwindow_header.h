#ifndef VIEW_MAINHEADER_H
#define VIEW_MAINHEADER_H

#include <view.h>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMenu>
#include <model_user.h>
#include <QPropertyAnimation>
class ViewMainWindowHeader : public View {

Q_OBJECT

private:
    static const int MENU_WIDTH;
	QLabel* usernameLabel;
	QLabel* titleLabel;
	QHBoxLayout* layout;

	QPushButton* menuButton;
	QMenu* menu;
    QActionGroup* menuActions;
    QPropertyAnimation* menuAnimation1;
    QPropertyAnimation* menuAnimation2;
    bool menuToggle;

	QAction* currentSelectedMenuAction;
	QString textColor;

	void updateMenuActions();

public:
	ViewMainWindowHeader(QWidget* parent = 0);

	QMenu* getMenu() const;
    void setTitle(const QString& pTitle);
	void setLoggedInView(ModelUser* currentUser);
	void setLoggedOutView();

	virtual void paintEvent(QPaintEvent *pe) override;

public slots:
    void showMenu();

signals:
	void mainMenuActionClicked(QAction*) const;
	void showMenu() const;

};

#endif // VIEW_MAINHEADER_H

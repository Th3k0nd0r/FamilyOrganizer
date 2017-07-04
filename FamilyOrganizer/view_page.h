#ifndef VIEW_PAGE_H
#define VIEW_PAGE_H

#include <view.h>
#include <QWidget>
#include <model_user.h>

class ViewPage : public View {

private:
	QString pageTitle;

public:
	ViewPage(const QString& pTitle, QWidget* parent=0);
	QString getPageTitle() const;
};

#endif // VIEW_PAGE_H

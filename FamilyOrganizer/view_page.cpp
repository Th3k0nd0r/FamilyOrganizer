#include "view_page.h"

ViewPage::ViewPage(const QString& pTitle, QWidget* parent) :
	View(parent),
	pageTitle(pTitle) { }

QString ViewPage::getPageTitle() const {
	return pageTitle;
}

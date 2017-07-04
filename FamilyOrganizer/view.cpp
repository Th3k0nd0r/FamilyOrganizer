#include "view.h"
#include <QLayoutItem>
#include <QLayout>

View::View(QWidget* parent) :
	QWidget(parent) { }


void View::clearLayout(QLayout *layout, int from) {
	QLayoutItem *item = layout->takeAt(from);
	while(item) {
		if (item->layout()) {
			clearLayout(item->layout());
			delete item->layout();
		}
		if (item->widget()) {
			delete item->widget();
		}
		delete item;

		item = layout->takeAt(from);
	}

}

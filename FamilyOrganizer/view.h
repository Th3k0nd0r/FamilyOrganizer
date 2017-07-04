#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
class View : public QWidget {

public:
	View(QWidget* parent = 0);
	static void clearLayout(QLayout* layout, int from=0);
};

#endif // VIEW_H

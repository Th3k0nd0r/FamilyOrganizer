#include <QApplication>
#include <iostream>
#include <controller_main.h>
#include <QStyleFactory>

int main(int argc, char *argv[]) {
	QApplication qt(argc, argv);

	ControllerMain mainController;
	mainController.startApp();

	return qt.exec();
}

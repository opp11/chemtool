#include <QtGui/QApplication>
#include <QtGui/QWidget>
#include "chemtool.h"

int main(int argc, char** argv){
	QApplication app(argc, argv);

	QWidget wnd;
	wnd.resize(250, 150);
	wnd.setWindowTitle("Chemtool");
	wnd.show();

	return app.exec();
}

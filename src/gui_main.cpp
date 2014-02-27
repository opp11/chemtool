#include <QtGui/QApplication>
#include <QtGui/QWidget>
#include <QtGui/QGridLayout>
#include <QtGui/QPushButton>
#include <QtGui/QLineEdit>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include "chemtool.h"

class win : public QWidget {
public:
	win(QWidget* app = nullptr);
private:
	void process_input();

	QGridLayout grid;
	QLabel err_lbl;
	QLineEdit in_txtbox;
	QPushButton calc_btn;
	QLabel totmm_lbl;
	QLabel unit_lbl;
	QLineEdit totmm_txtbox;
	QListWidget elem_lst;
};

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	win wnd;

	return app.exec();
}

win::win(QWidget* app) :
	QWidget(app),
	grid(this),
	err_lbl(this),
	in_txtbox(this),
	calc_btn("Calculate", this),
	totmm_lbl("Total Molar Mass:", this),
	unit_lbl("g/mol", this),
	totmm_txtbox(this),
	elem_lst(this)
{
	//setup the window
	this->setWindowTitle("chemtool");
	this->resize(300, 250);
	this->setMinimumHeight(250);
	this->setMinimumWidth(250);

	//setup the grid
	grid.setRowMinimumHeight(0, 20);
	grid.setRowMinimumHeight(2, 40);
	
	//setup the error label
	err_lbl.setAlignment(Qt::AlignLeft | Qt::AlignBottom);

	//setup the input textbox
	in_txtbox.setAlignment(Qt::AlignLeft | Qt::AlignTop);
	grid.addWidget(&in_txtbox, 1, 0, 1, 3);

	//setup the button which starts the processing
	grid.addWidget(&calc_btn, 2, 0, 1, 3, Qt::AlignCenter);
	connect(&calc_btn, SIGNAL(clicked()), this, SLOT(process_input));

	grid.addWidget(&totmm_lbl, 3, 0, 1, 1);
	
	grid.addWidget(&unit_lbl, 3, 2, 1, 1);

	totmm_txtbox.setReadOnly(false);
	grid.addWidget(&totmm_txtbox, 3, 1, 1, 1);

	grid.addWidget(&elem_lst, 4, 0, 1, 3);

	this->show();
}

void win::process_input()
{

}

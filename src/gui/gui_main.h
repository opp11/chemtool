#include <QtGui/QApplication>
#include <QtGui/QWidget>
#include <QtGui/QGridLayout>
#include <QtGui/QPushButton>
#include <QtGui/QLineEdit>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtGui/QMessageBox>
#include <QtGui/QFont>
#include <stdio.h>
#include "chemtool.h"

class win : public QWidget {
	Q_OBJECT
public:
	win(QWidget* app = NULL);
	virtual ~win(){};

public slots:
	void do_process_input();

private:	
	void report_mem_err();

	QGridLayout grid;
	QLabel err_lbl;
	QLineEdit in_txtbox;
	QPushButton calc_btn;
	QLabel totmm_lbl;
	QLabel unit_lbl;
	QLineEdit totmm_txtbox;
	QListWidget elem_lst;
};
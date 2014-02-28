#include "gui_main.h"

//Error reporting will be redirected to the string err_msg.
//If an error values is returned the error message will then be in err_msg,
static QString err_msg;
static void gui_err_reporter(int err, const char* msg);

int main(int argc, char** argv)
{
	set_err_reporter(gui_err_reporter);

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
	err_lbl.setWordWrap(true);
	grid.addWidget(&err_lbl, 0, 0, 1, 3);

	//setup the input textbox
	in_txtbox.setAlignment(Qt::AlignLeft | Qt::AlignTop);
	grid.addWidget(&in_txtbox, 1, 0, 1, 3);

	//setup the button which starts the processing
	grid.addWidget(&calc_btn, 2, 0, 1, 3, Qt::AlignCenter);
	connect(&calc_btn, SIGNAL(clicked()), this, SLOT(do_process_input()));

	//setup the output for the total molar mass
	totmm_txtbox.setReadOnly(false);
	totmm_txtbox.setAlignment(Qt::AlignRight);
	grid.addWidget(&totmm_txtbox, 3, 1, 1, 1);
	grid.addWidget(&totmm_lbl, 3, 0, 1, 1);
	grid.addWidget(&unit_lbl, 3, 2, 1, 1);

	//setup the element list
	QFont font;
	font.setStyleHint(QFont::Monospace);
	elem_lst.setFont(font);
	grid.addWidget(&elem_lst, 4, 0, 1, 3);

	this->show();
}

void win::do_process_input()
{
	if (in_txtbox.text().length() < 1)
		return;

	int err = 0;
	double tot_mm = 0.0f;
	char elem_data[BUFSIZ] = {0};

	err_lbl.setText("");
	struct elem_vec* evec = create_elem_vec(
		in_txtbox.text().toUtf8().constData());
	if (!evec){
		report_mem_err();
		goto exit;
	}

	err = process_input(in_txtbox.text().toUtf8().constData(), evec);
	//handle any errors
	if (err){
		switch (err){
		case EOOMEM:
			report_mem_err();
			break;
		case EFOPEN: 
		case EDBFMT:
			QMessageBox::critical(this, "Database error", err_msg);
			break;
		case EENAME:
		case EARGFMT:
			err_lbl.setText(
				QString("<font color='red' size='3'>%1</font>").
				arg(err_msg));
			break;
		}
		goto exit;
	}

	//if no errors occured output all the data
	for (int i = 0; i < evec->size; i++){
		tot_mm += evec->elms[i].weight * evec->elms[i].quant;
		snprintf(elem_data, BUFSIZ, "%s%6i    %10f g/mol    %s",
			evec->elms[i].sname, evec->elms[i].quant,
			evec->elms[i].weight, evec->elms[i].lname);
		elem_lst.addItem(elem_data);
	}
	totmm_txtbox.setText(QString::number(tot_mm));

exit:
	destroy_elem_vec(evec);
}

void win::report_mem_err()
{	
	//A memory allocation was unsuccesful. This is critical so inform
	//the user and exit the program.
	QMessageBox::critical(this, "Memory error", err_msg);
	QApplication::quit();
}

static void gui_err_reporter(int err, const char* msg)
{
	err_msg.clear();
	err_msg += get_base_err_msg(err);
	err_msg += msg;
}
#!/usr/bin/python
import chemtool
import sys
from PyQt4 import QtGui, QtCore

"""
Makes a gui for the chemtool program, making it easier to use the program.
"""

class Win(QtGui.QWidget):
    def __init__(self):
        super(Win, self).__init__()
        self.build_gui()
        self.show()

    def build_gui(self):
        #set up window
        self.resize(370, 250)
        self.setMinimumWidth(300)
        self.setMinimumHeight(250)
        self.setWindowTitle('Chemtool')

        global_grid = QtGui.QGridLayout()

        #make the error reporting label
        self.err_lbl = QtGui.QLabel('', self)
        self.err_lbl.setWordWrap(True)
        global_grid.addWidget(self.err_lbl, 0, 0, 1, 3,
		alignment=QtCore.Qt.AlignBottom)

        #make the textbox used for input
        self.input_box = QtGui.QLineEdit(self)
        global_grid.addWidget(self.input_box, 1, 0, 1, 3)

        #make the button used to start the calculation
        self.calc_btn = QtGui.QPushButton('Calculate', self)
        self.calc_btn.setToolTip("Get the molecule's data")
        self.setSizePolicy(QtGui.QSizePolicy.Fixed, QtGui.QSizePolicy.Fixed)
        self.calc_btn.clicked.connect(self.process_input)
        global_grid.addWidget(self.calc_btn, 2, 0, 1, 3,
		alignment=QtCore.Qt.AlignCenter | QtCore.Qt.AlignCenter)

        #set up the output of the total molar mass
        self.totmm_lbl = QtGui.QLabel('Total Molar Mass:', self)
        global_grid.addWidget(self.totmm_lbl, 3, 0)

        self.totmm_box = QtGui.QLineEdit(self)
        self.totmm_box.setReadOnly(True)
        self.totmm_box.setAlignment(QtCore.Qt.AlignRight)
        global_grid.addWidget(self.totmm_box, 3, 1)

	self.mm_unit_lbl = QtGui.QLabel('g/mol', self)
        global_grid.addWidget(self.mm_unit_lbl, 3, 2)

        #set up the list with the elements
        self.elem_list = QtGui.QListWidget(self)
        self.elem_list.setSizePolicy(QtGui.QSizePolicy.Expanding,
		QtGui.QSizePolicy.Expanding)
        self.elem_list.setFont(QtGui.QFont('Monospace', 10))
        global_grid.addWidget(self.elem_list, 4, 0, 1, 3)

        #setup the layout of the grid
        global_grid.setRowMinimumHeight(0, 20)
        global_grid.setRowMinimumHeight(2, 40)
        self.setLayout(global_grid)

    def process_input(self, event):
        #clear all outputs
        self.elem_list.clear()
        self.totmm_box.setText('')
        self.err_lbl.setText('')

        #attempt to get the element data
        try:
            elems = chemtool.get_elem_data(str(self.input_box.text()))
        except NameError as err:
            #something is wrong with the user's input, so display what is wrong
            self.err_lbl.setText(
		"<font color='red' size=2>*{}</font>".format(err))
        except UnicodeEncodeError as err:
            #on a unicode encoding error we display an argument format error
            self.err_lbl.setText("<font color='red' size=2>*{}unrecognised character. Please only use letters, numbers and parentheses.</font>".format(
		chemtool.get_base_err_msg(chemtool.err_arg_format)))
        except IOError as err:
            #something is wrong with the databse
            QtGui.QMessageBox.critical(self, "Database error", str(err))
        except MemoryError as err:
            #we have run out of memory
            #display an error message and exit
            QtGui.QMessageBox.critical(self, "Error - ran out of memory",
		"The program ran out of RAM while doing a calculation and will now exit")
            QtGui.QApplication.quit()
        except RuntimeError as err:
            #an unknown error occurred so warn the user
            QtGui.QMessageBox.critical(self, "Unknown error", str(err))
        else:
            #the parsing was succesful so if something was returned 
            #display the data
            if len(elems) > 0:
                total_mm = 0.0
                for (sname, lname, quant, weight) in elems:
                    total_mm += weight * quant
                    self.elem_list.addItem("{0}{1:>6}    {2:>12.7f}    {3}".
			format(sname, quant, weight, lname))
                self.totmm_box.setText("{:.7f}".format(total_mm))

if __name__ == '__main__':
    app = QtGui.QApplication(sys.argv)
    win = Win()
    app.exec_()

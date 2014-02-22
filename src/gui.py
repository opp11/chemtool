#!/usr/bin/python
import chemtool
import sys
from PyQt4 import QtGui, QtCore

class Win(QtGui.QWidget):
    def __init__(self):
        super(Win, self).__init__()
        self.build_gui()
        self.show()

    def build_gui(self):
        #set up window
        self.resize(300, 250)
        self.setWindowTitle('Chemtool')

        global_grid = QtGui.QGridLayout()

        #make the textbox used for input
        self.input_box = QtGui.QLineEdit(self)
        global_grid.addWidget(self.input_box, 1, 0, 1, 3)

        #make the button used to start the calculation
        self.calc_btn = QtGui.QPushButton('Calculate', self)
        self.calc_btn.setToolTip("Get the molecule's data")
        self.setSizePolicy(QtGui.QSizePolicy.Fixed, QtGui.QSizePolicy.Fixed)
        self.calc_btn.clicked.connect(self.process_input)
        global_grid.addWidget(self.calc_btn, 2, 0, 1, 3,
		alignment=QtCore.Qt.AlignCenter | QtCore.Qt.AlignTop)

        #set up the output of the total molar mass
        self.totmm_lbl = QtGui.QLabel('Total Molar Mass:', self)
        global_grid.addWidget(self.totmm_lbl, 3, 0)

        self.totmm_box = QtGui.QLineEdit(self)
        self.totmm_box.setReadOnly(True)
        global_grid.addWidget(self.totmm_box, 3, 1)

	self.mm_unit_lbl = QtGui.QLabel('g/mol', self)
        global_grid.addWidget(self.mm_unit_lbl, 3, 2)

        #set up the list with the elements
        self.elem_list = QtGui.QListWidget(self)
        self.elem_list.setSizePolicy(QtGui.QSizePolicy.Expanding,
		QtGui.QSizePolicy.Expanding)
        global_grid.addWidget(self.elem_list, 4, 0, 1, 3)

        #setup the layout of the grid
        global_grid.setRowMinimumHeight(0, 30)
        self.setLayout(global_grid)

    def process_input(self, event):
        elems = chemtool.get_elem_data(str(self.input_box.text()))
        total_mm = 0.0
        for (sname, lname, quant, weight) in elems:
             total_mm += weight * quant
        self.totmm_box.setText("{:.7f}".format(total_mm))

if __name__ == '__main__':
    app = QtGui.QApplication(sys.argv)
    win = Win()
    app.exec_()

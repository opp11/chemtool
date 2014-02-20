#!/usr/bin/python
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
        global_grid.addWidget(self.input_box, 1, 0)

        #make the button used to start the calculation
        self.calc_btn = QtGui.QPushButton('Calculate', self)
        self.calc_btn.setToolTip("Get the molecule's data")
        self.setSizePolicy(QtGui.QSizePolicy.Fixed, QtGui.QSizePolicy.Fixed)
        global_grid.addWidget(self.calc_btn, 2, 0,
		alignment=QtCore.Qt.AlignCenter | QtCore.Qt.AlignTop)

        #set up the list with the elements
        self.elem_list = QtGui.QListWidget(self)
        self.elem_list.setSizePolicy(QtGui.QSizePolicy.Expanding,
		QtGui.QSizePolicy.Expanding)
        global_grid.addWidget(self.elem_list, 3, 0)

        #setup the layout of the grid
        global_grid.setColumnMinimumWidth(0, 300)
        global_grid.setRowMinimumHeight(0, 30)
        self.setLayout(global_grid)

if __name__ == '__main__':
    app = QtGui.QApplication(sys.argv)
    win = Win()
    app.exec_()

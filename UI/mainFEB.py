#!/usr/bin/env python

from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import *

class MainFEB(QWidget):
    '''
    The FEB panel of the main window.
    '''
    def __init__(self, parent=None):
        super(MainFEB, self).__init__(parent)
        self.groupBox = self.layout_ui()
    
    def layout_ui(self):
        # named widgets
        self.EditNFeb = QLineEdit(text='0')
        self.BtnConfFebInUse = QPushButton('Configure')
        self.BtnConfDAQ = QPushButton('Configure')

        groupBox = QGroupBox('FEB config/control')
        grid = QGridLayout()
        grid.addWidget(QLabel('Number of FEBs: '), 0, 0, Qt.AlignRight)
        grid.addWidget(self.EditNFeb, 0, 1)
        grid.addWidget(QLabel('FEB in use: '), 1, 0, Qt.AlignRight)
        grid.addWidget(self.BtnConfFebInUse, 1, 1)
        grid.addWidget(QLabel('DAQ parameters: '), 2, 0, Qt.AlignRight)
        grid.addWidget(self.BtnConfDAQ, 2, 1)
        groupBox.setLayout(grid)
        return groupBox

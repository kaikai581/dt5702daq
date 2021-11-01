#!/usr/bin/env python
'''
The main window script.
'''

from .ui_mainFEB import MainFEB
from .ui_mainDAQ import MainDAQ
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import *

class MainWindowUI(QWidget):
    def __init__(self, parent=None):
        super(MainWindowUI, self).__init__(parent)

        # layout the main window
        self.ui = dict()
        self.layout_main()

    def layout_main(self):
        grid = QGridLayout()
        
        # layout the FEB control panel
        self.ui['feb'] = MainFEB(self)
        grid.addWidget(self.ui['feb'].groupBox, 0, 0)

        # layout the DAQ control panel
        self.ui['daq'] = MainDAQ(self)
        grid.addWidget(self.ui['daq'].groupBox, 0, 1, 1, 4)

        self.setLayout(grid)

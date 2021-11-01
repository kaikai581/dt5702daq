#!/usr/bin/env python
'''
The main window script.
'''

from .mainFEB import MainFEB
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
        self.ui['feb'] = MainFEB(self)
        grid.addWidget(self.ui['feb'].groupBox, 0, 0)
        self.setLayout(grid)

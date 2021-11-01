#!/usr/bin/env python
'''
The DAQ controls on the main window.
'''

from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import *

class MainDAQ(QWidget):
    def __init__(self, parent=None):
        super(MainDAQ, self).__init__(parent)
        self.groupBox = self.layout_ui()
    
    def layout_ui(self):
        # named widgets
        self.BtnStartDAQ = QPushButton('Start DAQ')
        self.BtnStopDAQ = QPushButton('Stop DAQ')
        self.BtnParamScan = QPushButton('Configure')

        groupBox_outer = QGroupBox('DAQ Control')
        grid_outer = QGridLayout()
        groupBox_single = QGroupBox('Single Parameter')
        grid_single = QGridLayout()
        grid_single.addWidget(self.BtnStartDAQ, 0, 0)
        grid_single.addWidget(self.BtnStopDAQ, 1, 0)
        groupBox_single.setLayout(grid_single)
        groupBox_scan = QGroupBox('Parameter Scan')
        grid_scan = QGridLayout()
        grid_scan.addWidget(self.BtnParamScan, 0, 0)
        groupBox_scan.setLayout(grid_scan)
        grid_outer.addWidget(groupBox_single, 0, 0)
        grid_outer.addWidget(groupBox_scan, 0, 1)
        groupBox_outer.setLayout(grid_outer)
        return groupBox_outer

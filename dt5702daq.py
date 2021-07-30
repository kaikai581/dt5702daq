#!/usr/bin/env python

'''
DT5702DAQ, a data acquisition software package with CAEN's DT5702 front-end
board for photosensor characterization.
Developed in 2021 by Shih-Kai Lin <shihkailin78@gmail.com>
This is the entry script of the project.

This program is free software: you can redistribute it and/or modify
it under the terms of the MIT License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
MIT License for more details.
'''

import sys

# Check mandatory external dependences
# PyQt5
try:
    from PyQt5 import QtCore, QtGui, QtWidgets
except ImportError as err:
    print('PyQt5 could not be found, you must install it.')
    raise err

# Qt application definition
app = QtWidgets.QApplication(sys.argv)
app.setOrganizationName('LSU')
app.setApplicationName('dt5702daq')

# import internal libraries
import UI

sys.exit(app.exec_())

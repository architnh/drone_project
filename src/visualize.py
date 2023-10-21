import pyqtgraph as pg
 
# importing QtCore and QtGui from the pyqtgraph module
from pyqtgraph.Qt import QtCore, QtGui
 
# importing numpy as np
import numpy as np
 
# define the data
title = "GeeksforGeeks PyQtGraph"
 
# y values to plot by line 1
y = [2, 8, 6, 8, 6, 11, 14, 13, 18, 19]
 
# y values to plot by line 2
y2 = [3, 1, 5, 8, 9, 11, 16, 17, 14, 16]
x = range(0, 10)
 
# create plot object
plt = pg.plot()
 
# showing x and y grids
plt.showGrid(x = True, y = True)
 
# adding legend
plt.addLegend()
 
# set properties of the label for y axis
plt.setLabel('left', 'Vertical Values', units ='y')
 
# set properties of the label for x axis
plt.setLabel('bottom', 'Horizontal Values', units ='s')
 
# setting horizontal range
plt.setXRange(0, 10)
 
# setting vertical range
plt.setYRange(0, 20)
 
# setting window title
plt.setWindowTitle(title)
 
# plotting line in green color
line1 = plt.plot(x, y, pen ='g', symbol ='x', symbolPen ='g', symbolBrush = 0.2, name ='green')
 
# plotting line2 with blue color
line2 = plt.plot(x, y2, pen ='b', symbol ='o', symbolPen ='b', symbolBrush = 0.2, name ='blue')
 
 
 
# main method
if __name__ == '__main__':
     
    # importing system
    import sys
     
    # Start Qt event loop unless running in interactive mode or using 
    if (sys.flags.interactive != 1) or not hasattr(QtCore, 'PYQT_VERSION'):
        QtGui.QApplication.instance().exec_()
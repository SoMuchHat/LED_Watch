
"""
Created on Mon Aug 10 11:06:06 2015

This script generates a EAGLE .scp file with necessary positions and angles
required to place 360 leds in a circular pattern.

Specify the distance each row of leds should be from the center of the circle

@author: Sean
"""
import math
from pcbnew import *


pcb = GetBoard()

r1 = 600 # mils
r2 = 500
r3 = 400
leds_row1 = 60
leds_row2 = 60
leds_row3 = 12

index = 0
currentRow = 1
currentCol = 1
rotate_col = 0

center_x = 0
center_y = 0

while index < 120:
	if currentCol == 13:
		currentRow = currentRow + 2
		currentCol = 1
		
	part = pcb.FindModuleByReference("R" + str(currentRow) + "C" + str(currentCol))
	xPos = center_x + math.sin(2*np.pi / leds_row1 * rotate_col) * -1 * r1
	yPos = center_y + math.cos(2*np.pi / leds_row1 * rotate_col) * r1
	#f.write("MOVE \'R" + str(currentRow) + "C" + str(currentCol) + "\' (" + str(xPos) + " " + str(yPos) + ")\n")
	#f.write("ROTATE =R" + str(360.0/leds_row1*rotate_col) + " \'R" + str(currentRow) + "C" + str(currentCol) + "\'\n")
	
	angle = (360.0/leds_row1*rotate_col)
	part.SetPosition(wxPoint(FromMils(xPos), FromMils(yPos)))
	part.SetOrientation(angle * -10)
	
	index = index + 1
	currentRow = currentRow + 1
	
	part = pcb.FindModuleByReference("R" + str(currentRow) + "C" + str(currentCol))
	xPos = center_x + math.sin(2*np.pi / leds_row2 * rotate_col) * -1 * r2
	yPos = center_y + math.cos(2*np.pi / leds_row2 * rotate_col) * r2
	
	#f.write("MOVE \'R" + str(currentRow) + "C" + str(currentCol) + "\' (" + str(xPos) + " " + str(yPos) + ")\n")
	#f.write("ROTATE =R" + str(360.0/leds_row2*rotate_col) + " \'R" + str(currentRow) + "C" + str(currentCol) + "\'\n")
	angle = (360./leds_row2*rotate_col)
	part.SetPosition(wxPoint(FromMils(xPos), FromMils(yPos)))
	part.SetOrientation(angle * -10)
	
	index = index + 1
	currentRow = currentRow - 1
	currentCol = currentCol + 1
	rotate_col = rotate_col + 1
	
currentRow = 11
currentCol = 1

while index < 132:

	part = pcb.FindModuleByReference("R" + str(currentRow) + "C" + str(currentCol))
	xPos = center_x + math.sin(2*np.pi / leds_row3 * index) * -1 * r3
	yPos = center_y + math.cos(2*np.pi / leds_row3 * index) * r3
	#f.write("MOVE \'R" + str(currentRow) + "C" + str(currentCol) + "\' (" + str(xPos) + " " + str(yPos) + ")\n")
	#f.write("ROTATE =R" + str(360.0/leds_row3*index) + " \'R" + str(currentRow) + "C" + str(currentCol) + "\'\n")
	angle = (360./leds_row2*index)
	part.SetPosition(wxPoint(FromMils(xPos), FromMils(yPos)))
	part.SetOrientation(angle * -10)
	index = index + 1
	currentCol = currentCol + 1

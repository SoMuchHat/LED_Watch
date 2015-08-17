# -*- coding: utf-8 -*-
"""
Created on Mon Aug 10 11:06:06 2015

This script generates a EAGLE .scp file with necessary positions and angles
required to place 360 leds in a circular pattern.

Specify the distance each row of leds should be from the center of the circle

@author: Sean
"""
import numpy as np

r1 = 0.6 # inches
r2 = 0.5
r3 = 0.4

leds_row1 = 60
leds_row2 = 60
leds_row3 = 12

f = open('circular_placement_script.scr', 'w')

index = 0
currentRow = 1
currentCol = 1
while index < leds_row1:
    if currentCol == 13:
        currentRow = currentRow + 1
        currentCol = 1
    xPos = np.sin(2*np.pi / leds_row1 * index) * -1 * r1
    yPos = np.cos(2*np.pi / leds_row1 * index) * r1
    f.write("MOVE \'R" + str(currentRow) + "C" + str(currentCol) + "\' (" + str(xPos) + " " + str(yPos) + ")\n")
    f.write("ROTATE =R" + str(360.0/leds_row1*index) + " \'R" + str(currentRow) + "C" + str(currentCol) + "\'\n")
    index = index + 1
    currentCol = currentCol + 1

index = 0
while index < leds_row2:
    if currentCol == 13:
        currentRow = currentRow + 1
        currentCol = 1
    xPos = np.sin(2*np.pi / leds_row2 * index) * -1 * r2
    yPos = np.cos(2*np.pi / leds_row2 * index) * r2
    f.write("MOVE \'R" + str(currentRow) + "C" + str(currentCol) + "\' (" + str(xPos) + " " + str(yPos) + ")\n")
    f.write("ROTATE =R" + str(360.0/leds_row2*index) + " \'R" + str(currentRow) + "C" + str(currentCol) + "\'\n")
    index = index + 1
    currentCol = currentCol + 1
    
index = 0
while index < leds_row3:
    if currentCol == 13:
        currentRow = currentRow + 1
        currentCol = 1
    xPos = np.sin(2*np.pi / leds_row3 * index) * -1 * r3
    yPos = np.cos(2*np.pi / leds_row3 * index) * r3
    f.write("MOVE \'R" + str(currentRow) + "C" + str(currentCol) + "\' (" + str(xPos) + " " + str(yPos) + ")\n")
    f.write("ROTATE =R" + str(360.0/leds_row3*index) + " \'R" + str(currentRow) + "C" + str(currentCol) + "\'\n")
    index = index + 1
    currentCol = currentCol + 1
    
f.close()
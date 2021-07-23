# GridSquare


## ReadGPS.c

This program uses libgps to read data from gpsd running on the localhost (hard-coded to localhost on port 2947), and will display a valid latitude and longitude. 
Additional information will be output to stderr, including when an invalid position is received.

## GridSquare.cpp

Given a latitude and longitude, this program will calculate its gridsquare using calculations from http://n1sv.com/PROJECTS/How%20to%20calculate%20your%208-digit%20grid%20square.pdf

## GridToGPS.cpp

Given a six-character gridsquare, this program will calculate the approximage latitude and longitude that corresponds.

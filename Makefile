
all: gps GridSquare GridToGPS

gps: ReadGPS.c
	gcc -o gps ReadGPS.c -lm -lgps

GridSquare: GridSquare.cpp
	g++ GridSquare.cpp -o GridSquare

GridToGPS: GridToGPS.cpp
	g++ GridToGPS.cpp -o GridToGPS

clean:
	rm -f gps GridSquare GridToGPS

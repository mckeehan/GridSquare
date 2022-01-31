
all: gps GridSquare GridToGPS

gps: ReadGPS.c
	gcc -o gps ReadGPS.c -lm -lgps

GridSquare: GridSquare.cpp
	g++ GridSquare.cpp -o GridSquare

GridToGPS: GridToGPS.cpp
	g++ GridToGPS.cpp -o GridToGPS

ReadGPSdaemon: ReadGPSdaemon.c
	gcc -o ReadGPSdaemon ReadGPSdaemon.c -lm -lgps

UDPServer: UDPServer.c
	gcc -o UDPServer UDPServer.c

UDPClient: UDPClient.c
	gcc -o UDPClient UDPClient.c

clean:
	rm -f gps GridSquare GridToGPS

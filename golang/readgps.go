package main

import (
	"bufio"
	"encoding/json"
	"fmt"
	"log"
	"net"
)

type TPVReport struct {
	Class string  `json:"class"`
	Lat   float64 `json:"lat"`
	Lon   float64 `json:"lon"`
	Alt   float64 `json:"alt"`
	Mode  int     `json:"mode"`
}

func main() {
	// Connect to GPSD using raw TCP
	conn, err := net.Dial("tcp", "localhost:2947")
	if err != nil {
		log.Fatalf("Failed to connect to GPSD: %v", err)
	}
	defer conn.Close()

	// Send the WATCH command to start receiving reports
	fmt.Fprintf(conn, "?WATCH={\"enable\":true,\"json\":true}\n")

	// Create a buffered reader to read the response
	reader := bufio.NewReader(conn)

	// Continuously read data from the GPSD server
	for {
		// Read a line of response from GPSD
		line, err := reader.ReadString('\n')
		if err != nil {
			log.Fatalf("Failed to read from GPSD: %v", err)
		}

		// Parse the JSON response
		var report TPVReport
		err = json.Unmarshal([]byte(line), &report)
		if err != nil {
			log.Println("Failed to parse GPSD response:", err)
			continue
		}

		// Handle TPV reports
		if report.Class == "TPV" && report.Mode >= 2 {
			// fmt.Printf("Latitude: %f, Longitude: %f\n", report.Lat, report.Lon)
			fmt.Printf("%f %f\n", report.Lat, report.Lon)
			if report.Mode == 3 {
        // altitudeInFeet := report.Alt * 3.28084 // Convert altitude from meters to feet
        // fmt.Printf("Altitude: %.2f feet\n", altitudeInFeet)
			} else {
				// fmt.Println("Altitude: N/A")
			}
      break;
		}
	}
}

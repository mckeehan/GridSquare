#!/bin/bash
# Fetch the forcast for the next three periods
# Details on the API are at https://www.weather.gov/documentation/services-web-api
#
# This will do it in one line
# wget -q -O - $(wget -q -O - https://api.weather.gov/points/$(./gps 2>/dev/null | sed 's/ /,/') | jq -r .properties.forecast) | jq -r '.properties.periods|map(select(.number < 4 and .number > 0)| "**" + .name + "** | " + .detailedForecast) | .[]'
#
# Use gps to get lat,long
LOC=$(./gps | sed 's/ /,/')
# echo $LOC
# https://weather-gov.github.io/api/gridpoints
FURL=$(wget -q -O - https://api.weather.gov/points/$(./gps 2>/dev/null | sed 's/ /,/') | jq -r .properties.forecast)
# echo "$FURL"
echo
wget -q -O - $FURL | jq -r '.properties.periods|map(select(.number < 4 and .number > 0)| "**" + .name + "** | " + .detailedForecast) | .[]'

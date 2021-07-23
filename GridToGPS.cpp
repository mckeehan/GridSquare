/*
 * Logic derived from https://github.com/gravypod/maidenhead/blob/master/maidenhead.sql
 *
 */
#include <iostream>
#include <cmath>
#include <string.h>

using namespace std;

double grid2lat(char *grid);
double grid2lon(char *grid);

void usage(char *name);

int main( int argc, char *argv[], char *envp[] )
{
  if( argc != 2 || strlen(argv[1]) != 6 ) usage(argv[0]);

  double lat = grid2lat(argv[1]);
  double lon = grid2lon(argv[1]);

  printf("%lf %lf\n", lat, lon);
}

void usage(char *name)
{
  fprintf(stderr, "usage: %s gridsquare\n\ngridsquare must be 6 characters", name);
  exit(EXIT_FAILURE);
}

/*

CREATE FUNCTION grid2lat(gridsquare VARCHAR(6)) RETURNS FLOAT(8, 4) BEGIN
	DECLARE lat FLOAT(8, 4) DEFAULT -90;
	IF LENGTH(gridsquare) >= 2 THEN
		SET lat = lat + ((ORD(SUBSTR(gridsquare, 2, 1)) - ORD('A')) * 10);
	END IF;
	IF LENGTH(gridsquare) >= 4 THEN
		SET lat = lat + (CAST(SUBSTR(gridsquare, 4, 1) as UNSIGNED) * 1);
	END IF;
	IF LENGTH(gridsquare) >= 6 THEN
		SET lat = lat + ((ORD(SUBSTR(gridsquare, 6, 1)) - ORD('a')) * (2.5 / 60));
	END IF;

	RETURN lat;
*/


double grid2lat(char *grid)
{
  double ret = -90.0;

  ret = ret + ((grid[1] - 'A') * 10);
  ret = ret + (grid[3] - '0');
  ret = ret + ((grid[5] - 'a') * ( 2.5 / 60.0 ));
  
  return ret;
}

/*
CREATE FUNCTION grid2lon(gridsquare VARCHAR(6)) RETURNS FLOAT(8, 4) BEGIN
	DECLARE lon FLOAT(8, 4) DEFAULT -180;
	IF LENGTH(gridsquare) >= 2 THEN
		SET lon = lon + ((ORD(SUBSTR(gridsquare, 1, 1)) - ORD('A')) * 20);
	END IF;
	IF LENGTH(gridsquare) >= 4 THEN
		SET lon = lon + (CAST(SUBSTR(gridsquare, 3, 1) as UNSIGNED) * 2);
	END IF;
	IF LENGTH(gridsquare) >= 6 THEN
		SET lon = lon + ((ORD(SUBSTR(gridsquare, 5, 1)) - ORD('a')) * (5   / 60));
	END IF;

	RETURN lon;
*/
double grid2lon(char *grid)
{
  double ret = -180;
  ret = ret + ((grid[0] - 'A') * 20);
  ret = ret + ((grid[2] - '0') * 2);
  ret = ret + ((grid[4] - 'a') * (5.0/60.0));

  return ret;
}

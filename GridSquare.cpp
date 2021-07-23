#include <iostream>
#include <cmath>

using namespace std;

/**
 * Calculations from http://n1sv.com/PROJECTS/How%20to%20calculate%20your%208-digit%20grid%20square.pdf
 */

void usage(char *name);
void calcLocator(char *dst, double lat, double lon);

int main( int argc, char *argv[], char *envp[] )
{
  char dst[10];
  double lat, lon;

  if( argc != 3 ) usage(argv[0]);

  sscanf(argv[1],"%lf",&lat);
  if( abs(lat) > 90 ) usage(argv[0]);

  sscanf(argv[2],"%lf",&lon);
  if( abs(lon) > 180 ) usage(argv[0]);

  calcLocator(dst, lat, lon);
  fprintf(stderr, "Latitude: %lf\nLongitude: %lf\nGrid Square: %s\n", lat, lon, dst);
  printf("%s\n", dst);
}

void usage(char *name)
{
  fprintf(stderr, "usage: %s Latitude Longitude\n", name);
  exit(EXIT_FAILURE);
}

void calcLocator(char *dst, double lat, double lon)
{
  int o1, o2, o3, o4;
  int a1, a2, a3, a4;
  double remainder;
  double oneTwelfth = 1.0/12.0;
  double oneTwentyFourth = 1.0/24.0;

  // longitude
  remainder = lon + 180.0;
  o1 = (int)(remainder / 20.0);
  remainder = remainder - (double)o1 * 20.0;
  o2 = (int)(remainder / 2.0);
  remainder = remainder - 2.0 * (double)o2;
  o3 = (int)(remainder / oneTwelfth);
  remainder = remainder - oneTwelfth * (double)o3;
  o4 = (int)(remainder/(oneTwelfth/10));

  // latitude
  remainder = lat + 90.0;
  a1 = (int)(remainder / 10.0);
  remainder = remainder - (double)a1 * 10.0;
  a2 = (int)(remainder);
  remainder = remainder - (double)a2;
  a3 = (int)(remainder / oneTwentyFourth);
  remainder = remainder - oneTwentyFourth * (double)a3;
  a4 = (int)(remainder / (oneTwentyFourth/10));

  dst[0] = (char)o1 + 'A';
  dst[1] = (char)a1 + 'A';
  dst[2] = (char)o2 + '0';
  dst[3] = (char)a2 + '0';
  dst[4] = (char)o3 + 'a';
  dst[5] = (char)a3 + 'a';
  dst[6] = (char)o4 + '0';
  dst[7] = (char)a4 + '0';
  dst[8] = (char)0;
}


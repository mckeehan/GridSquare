#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

#include <gps.h>
#include <math.h>

int readGPS();

struct gps_data_t valid_gps_data;

int main(void) {
  
  /* Our process ID and Session ID */
  pid_t pid, sid;
  
  /* Fork off the parent process */
  pid = fork();
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  /* If we got a good PID, then we can exit the parent process. */
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  /* Change the file mode mask */
  umask(0);
    
  /* Open any logs here */  
    
  /* Create a new SID for the child process */
  sid = setsid();
  if (sid < 0) {
    /* Log the failure */
    exit(EXIT_FAILURE);
  }
  

  
  /* Change the current working directory */
  if ((chdir("/")) < 0) {
    /* Log the failure */
    exit(EXIT_FAILURE);
  }
  
  /* Close out the standard file descriptors */
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
  
  /* Daemon-specific initialization goes here */
  
  /* The Big Loop */
  exit(readGPS());
}


int readGPS() {
  int rc;
  struct timeval tv;
  char message[1024];

  if ((rc = gps_open("localhost", "2947", &valid_gps_data)) == -1) {
    //log failure printf("code: %d, reason: %s\n", rc, gps_errstr(rc));
    return EXIT_FAILURE;
  }
  gps_stream(&valid_gps_data, WATCH_ENABLE | WATCH_JSON, NULL);

  while (1) {
    /* wait for 5 seconds to receive data */
    if (gps_waiting (&valid_gps_data, 5000000)) {
      /* read data */
      if ((rc = gps_read(&valid_gps_data)) == -1) {
        // log failure printf("error occured reading gps data. code: %d, reason: %s\n", rc, gps_errstr(rc));
      } else {
        /* Display data from the GPS receiver. */
        if ( //(valid_gps_data.status == STATUS_FIX) && 
             //(valid_gps_data.fix.mode == MODE_2D || valid_gps_data.fix.mode == MODE_3D) &&
             !isnan(valid_gps_data.fix.latitude) && 
             !isnan(valid_gps_data.fix.longitude) &&
             true) {
          //gettimeofday(&tv, NULL); EDIT: tv.tv_sec isn't actually the timestamp!
          // log success fprintf(stderr, "latitude: %f, longitude: %f, speed: %f, timestamp: %lf\n", valid_gps_data.fix.latitude, valid_gps_data.fix.longitude, valid_gps_data.fix.speed, valid_gps_data.fix.time); //EDIT: Replaced tv.tv_sec with valid_gps_data.fix.time
          //printf("%f %f", valid_gps_data.fix.latitude, valid_gps_data.fix.longitude);
          //break;
        } else {
          //fprintf(stderr, "no GPS data available\n");
        }
      }
    }
    sleep(3);
  }

  /* When you are done... */
  gps_stream(&valid_gps_data, WATCH_DISABLE, NULL);
  gps_close (&valid_gps_data);

  return EXIT_SUCCESS;
}


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int
run_wrapper(char *cmd) {
  system(cmd);
}

void
show_logs(char *cmd, char *logfile) {
  char buffer[100];
  char filename[255]; // Linux filename limit.  Theoretically could break on different filesystems
  int safe;
  FILE *fp;

  // If user ignores a string that is too long, fail.
  // The alternative would be to simply truncate it.
  if (strlen(logfile) + strlen(cmd) + 13 > 100) {
    printf("That filename is too long\n");
    exit(2);
  }

  fp = popen("ls /var/log | xargs -n 1 basename", "r");
  if (fp == NULL) {
    printf("Could not run ls or xargs\n");
    exit(3);
  }

  // Strictly only allow filenames that are within /var/log.
  // We could simply sanitize the string to exclude ".." or commands 
  // to avoid this search, but for simplicity of the POC we will just do this 
  safe = 0;
  while (fgets(filename, sizeof(filename)-1, fp) != NULL) {
    if (strstr(filename, logfile) != NULL) {
      safe = 1;
      break;
    }
  }

  if (!safe) {
    printf("File does not exist within /var/log/\n");
    exit(4);
  }

  sprintf(buffer, "%s -f /var/log/%s", cmd, logfile);

  run_wrapper(buffer);
}


int
main(int argc, char **argv) {
  printf("Display the log file\n");

  if(argc < 2) {
    printf("Usage: %s <log-file>\n\n", argv[0]);
    exit(1);
  }

  show_logs("/usr/bin/tail", argv[1]);
}

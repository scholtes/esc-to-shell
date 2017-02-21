#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int
run_wrapper(char *cmd) {
  system(cmd);
}

void
show_logs(char *cmd, char *logfile) {
  char buffer[100];

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

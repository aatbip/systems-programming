#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  if ((kill(atoi(argv[1]), SIGTERM)) == -1) {
    perror("kill");
    exit(EXIT_FAILURE);
  }
  exit(EXIT_SUCCESS);
}

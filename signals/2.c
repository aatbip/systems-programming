#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int sig) {
  if (sig == SIGTERM) {
    printf("SIGTERM invoked\n");
  }

  if (sig == SIGQUIT) {
    printf("Quiting normally...\n");
    exit(EXIT_SUCCESS);
  }
}

int main(int argc, char **argv) {
  if ((kill(atoi(argv[1]), atoi(argv[2]))) == -1) {
    perror("kill");
    exit(EXIT_FAILURE);
  }
  exit(EXIT_SUCCESS);

  pid_t pid;
  // new process
  if ((pid = fork() == 0)) {
    signal(SIGTERM, handler);
    signal(SIGQUIT, handler);
  }

  // old process
  if (pid > 0) {
    signal(SIGQUIT, handler);
    for (;;)
      if (kill(pid, atoi(argv[1])) == -1) {
        perror("kill");
      }
  }
}

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

  pid_t pid;
  // new process
  if ((pid = fork()) == 0) {
    printf("Child running... PID %d\n", getpid());
    signal(SIGTERM, handler);
    signal(SIGQUIT, handler);
  }

  // parent process
  if (pid > 0) {
    printf("Parent PID: %d\n", getpid());
    signal(SIGQUIT, handler);
    for (;;) {
      int s;
      scanf("%d", &s);
      printf("reading %d\n", s);
      if (kill(pid, s) == -1) {
        perror("kill");
        exit(EXIT_FAILURE);
      }
    }
  }
}

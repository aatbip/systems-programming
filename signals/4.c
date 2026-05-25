/*Analyzing what may possibly happen when sending multiple signals to a process concurrently.*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void sig_handle(int sig) {
  if (sig == SIGINT) {
    printf("%s triggered.", strsignal(sig));
  }
  if (sig == SIGTERM) {
    printf("%s triggered.", strsignal(sig));
    exit(EXIT_SUCCESS);
  }
}

int main(int argc, char *argv[]) {
  int proc;
  switch ((proc = fork())) {
  case -1:
    perror("fork");
    exit(EXIT_FAILURE);

  // child process
  case 0:
    break;

  // parent process
  default:
    break;
  }
}

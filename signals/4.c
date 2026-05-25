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
  if (sig == SIGTERM || sig == SIGCHLD) {
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
    if (signal(SIGINT, sig_handle) == SIG_ERR || signal(SIGTERM, sig_handle) == SIG_ERR) {
      perror("signal disposition");
      exit(EXIT_FAILURE);
    }
    /*Run child process forever until SIGTERM is received.*/
    for (;;)
      ;
    break;

  // parent process
  default:
    /*Register SIGCHLD in parent to terminate parent when child exits*/
    if (signal(SIGCHLD, sig_handle) == SIG_ERR) {
      perror("signal disposition");
      exit(EXIT_FAILURE);
    }
    int sig;
    printf("Enter signal identifier: ");
    scanf("%d\n", &sig);

    break;
  }
}

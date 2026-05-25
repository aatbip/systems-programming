/*Analyzing what may possibly happen when sending multiple signals to a process concurrently.*/

#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define THREAD_CNT 4

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
  pid_t pid;
  switch ((pid = fork())) {
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

    pthread_t *th = malloc(sizeof(pthread_t) * THREAD_CNT);

    for (;;) {
      int sig;
      printf("Enter signal identifier: ");
      scanf("%d\n", &sig);

      for (int i = 0; i < THREAD_CNT; i++) {
        if (pthread_create(&th[i], NULL, NULL, NULL) != 0) {
          perror("pthread_create");
        }
        pthread_detach(th[i]);
      }
    }

    break;
  }
}

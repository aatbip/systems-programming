/*Analyzing what may possibly happen when sending multiple signals to a process concurrently.*/

#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct sig_handler_param {
  pid_t pid;
  int sig;
} sig_handler_param_t;

#define THREAD_CNT 4

void *routine(void *p) {
  printf("Routine running...\n");
  sig_handler_param_t *param = (sig_handler_param_t *)p;
  if (kill(param->pid, param->sig) == -1) {
    perror("kill");
  }
  return NULL;
}

void sig_handle(int sig) {
  if (sig == SIGTERM) {
    printf("%s triggered.", strsignal(sig));
  }
  if (sig == SIGQUIT || sig == SIGCHLD) {
    printf("%s triggered.", strsignal(sig));
    printf("Exiting [pid] %d\n", getpid());
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
    printf("Child pid: %d\n", getpid());
    if (signal(SIGTERM, sig_handle) == SIG_ERR || signal(SIGQUIT, sig_handle) == SIG_ERR) {
      perror("signal disposition");
      exit(EXIT_FAILURE);
    }
    /*Run child process forever until SIGTERM is received.*/
    for (;;)
      ;
    break;

  // parent process
  default:
    printf("Parent pid: %d\n", getpid());
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
      sig_handler_param_t *param = malloc(sizeof(sig_handler_param_t));
      param->pid = pid;
      param->sig = sig;
      for (int i = 0; i < THREAD_CNT; i++) {
        if (pthread_create(&th[i], NULL, routine, param) != 0) {
          perror("pthread_create");
        }
        pthread_detach(th[i]);
      }
    }
    break;
  }
}

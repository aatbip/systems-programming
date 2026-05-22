#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void (*oldHandler)(int);

void newHandler(int sig) {
  //
  printf("\nhey %d\n", sig);
  exit(EXIT_FAILURE);
};

typedef void (*hd_t)(int);

extern void original_handler(int n) {}

hd_t test(int n, hd_t new_hd) {
  // something..

  return original_handler;
}

int main(void) {
  printf("pid: %d\n", getpid());
  oldHandler = signal(SIGSEGV, newHandler);
  sig_t s; // sighandler_t type alias

  if (oldHandler == SIG_ERR) {
    perror("signal");
    exit(EXIT_FAILURE);
  }

  // sleep(2);
  printf("do something...\n");

  int *a;
  a[1] = 100;

  // if (signal(SIGINT, SIG_DFL) == SIG_ERR) {
  //   perror("signal 1");
  //   exit(EXIT_FAILURE);
  // }
  // while (1)
  //   ;

  exit(EXIT_SUCCESS);
}

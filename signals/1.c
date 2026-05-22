#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void (*oldHandler)(int);

void newHandler(int sig) {
  //
  printf("\nhey %d\n", sig);
};

int main(void) {
  oldHandler = signal(SIGINT, newHandler);

  if (oldHandler == SIG_ERR) {
    perror("signal");
    exit(EXIT_FAILURE);
  }

  sleep(2);
  printf("do something...\n");

  if (signal(SIGINT, oldHandler) == SIG_ERR) {
    perror("signal 1");
    exit(EXIT_FAILURE);
  }
  sleep(2);

  exit(EXIT_SUCCESS);
}

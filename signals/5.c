#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_sig(sigset_t *set) {
  for (int i = 1; i < NSIG; i++) {
    if (sigismember(set, i)) {
      printf("sig %d %s\n", i, strsignal(i));
    }
  }
}

int main(void) {
  sigset_t oldset, newset;
  if (sigprocmask(0, NULL, &oldset) == -1) {
    perror("sigprocmask");
  }

  sigaddset(&newset, SIGQUIT);

  if (sigprocmask(SIG_BLOCK, &newset, &oldset) == -1) {
    perror("sigprocmask");
  }

  print_sig(&newset);
  printf("sleeping...\n");
  sleep(5);

  printf("Next SIGQUIT will be removed mask..\n");
  sigdelset(&newset, SIGQUIT);
  if (sigprocmask(SIG_SETMASK, &newset, &oldset) == -1) {
    perror("sigprocmask");
  }
  print_sig(&newset);
  sleep(5);

  exit(EXIT_SUCCESS);
}

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

  sigaddset(&newset, 1);
  sigaddset(&newset, 2);
  sigaddset(&newset, 3);
  sigaddset(&newset, 4);

  if (sigprocmask(SIG_BLOCK, &newset, &oldset) == -1) {
    perror("sigprocmask");
  }

  print_sig(&newset);

  exit(EXIT_SUCCESS);
}

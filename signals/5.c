#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_sig(sigset_t *set) {
  for (int i = 1; i < NSIG; i++) {
    if (sigismember(set, i)) {
      printf("%s\n", strsignal(i));
    }
  }
}

int main(void) {
  sigset_t oldset, newset;
  if (sigprocmask(0, NULL, &oldset) == -1) {
    perror("sigprocmask");
  }

  exit(EXIT_SUCCESS);
}

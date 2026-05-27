#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  sigset_t oldset;
  if (sigprocmask(0, NULL, &oldset) == -1) {
    perror("sigprocmask");
  }

  for (int i = 1; i < NSIG; i++) {
    if (sigismember(&oldset, i)) {
      printf("%s\n", strsignal(i));
    }
  }

  exit(EXIT_SUCCESS);
}

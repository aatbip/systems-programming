#include <bits/types/sigset_t.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  char *s = strsignal(atoi(argv[1]));
  printf("%s\n", s);

  sigset_t set;
  sigaddset(&set, 3);
  sigaddset(&set, 15);

  printf("%d\n", sigismember(&set, atoi(argv[1])));

  for (int i = 1; i < NSIG; i++) {
    if (sigismember(&set, i)) {
      printf("%d %s\n", i, strsignal(i));
    }
  }

  exit(EXIT_SUCCESS);
}

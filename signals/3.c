#include <bits/types/sigset_t.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  char *s = strsignal(atoi(argv[1]));
  printf("%s\n", s);

  sigset_t set;
  printf("2nd bit set? %d\n", (((set.__val[0] >> 2) & 1) == 1));
  printf("14th bit set? %d\n", (((set.__val[0] >> 14) & 1) == 1));
  printf("0st bit set? %d\n", (((set.__val[0] >> 0) & 1) == 1));
  sigaddset(&set, 3);
  sigaddset(&set, 15);
  sigaddset(&set, 1);
  printf("2nd bit set? %d\n", (((set.__val[0] >> 2) & 1) == 1));
  printf("14th bit set? %d\n", (((set.__val[0] >> 14) & 1) == 1));
  printf("0st bit set? %d\n", (((set.__val[0] >> 0) & 1) == 1));

  // printf("%d\n", sigismember(&set, atoi(argv[1])));
  //
  // for (int i = 1; i < NSIG; i++) {
  //   if (sigismember(&set, i)) {
  //     printf("%d %s\n", i, strsignal(i));
  //   }
  // }
  //
  exit(EXIT_SUCCESS);
}

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  char *s = strsignal(atoi(argv[1]));
  printf("%s\n", s);

  psignal(atoi(argv[1]), "Didn't work?");

  exit(EXIT_SUCCESS);
}

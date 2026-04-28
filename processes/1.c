#define _GNU_SOURCE

#include <linux/limits.h>
#include <stdlib.h>

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
  printf("%d\n", getpid());
  printf("%s\n", program_invocation_name);
  printf("%s\n", program_invocation_short_name);
  printf("%ld\n", sysconf(_SC_PAGE_SIZE));
  printf("%d\n", ARG_MAX);
  printf("SHELL: %s\n", getenv("SHELL"));
  char buf[64];
  setenv("SHELL", getcwd(buf, sizeof(buf)), 1);
  printf("DEMO: %s\n", getenv("DEMO"));
  // extern char **environ;
  // for (char **p = environ; *p != NULL; p++) {
  //   puts(*p);
  // }
  if (setenv("DEMO1", "milo", 1) == -1) {
    perror("setenv");
  }
  sleep(40);
  return 0;
}

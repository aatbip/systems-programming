#include <linux/limits.h>
#define _GNU_SOURCE

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
  return 0;
}

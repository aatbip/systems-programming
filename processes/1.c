#define _GNU_SOURCE

#include <errno.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
  printf("%d\n", getpid());
  printf("%s\n", program_invocation_name);
  printf("%s\n", program_invocation_short_name);
  printf("%ld\n", sysconf(_SC_PAGE_SIZE));
  sleep(15);
  return 0;
}

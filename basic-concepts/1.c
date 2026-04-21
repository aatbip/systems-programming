/*All files in this directory deals with general basic concepts.*/

#include <asm-generic/errno-base.h>
#include <asm-generic/errno.h>
#include <errno.h>
#include <gnu/libc-version.h>
#include <stdio.h>

int main(void) {
  printf("%s\n", gnu_get_libc_version());
  errno = EINPROGRESS; // to demo perror
  perror("demo");
  return 0;
}

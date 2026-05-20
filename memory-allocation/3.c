#include <asm-generic/errno-base.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <unistd.h>

void *al(long incr) {
  void *cb = (void *)syscall(SYS_brk, 0);
  if (brk(cb + incr) == -1) {
    errno = EINVAL;
    return NULL;
  }
  return cb;
}

int main(void) {
  void *cb0 = (void *)syscall(SYS_brk, 0);
  void *p;
  if ((p = al(1024)) == NULL) {
    perror("err");
  }

  return 0;
}

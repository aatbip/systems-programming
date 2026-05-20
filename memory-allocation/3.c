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

void *dec(long decr) {
  void *cb = (void *)syscall(SYS_brk, 0);
  if (brk(cb - decr) == -1) {
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
  void *cb1 = (void *)syscall(SYS_brk, 0);
  if ((p = dec(1024)) == NULL) {
    perror("err");
  }
  void *cb2 = (void *)syscall(SYS_brk, 0);
  printf("cb0: %p\ncb1: %p\ncb2: %p\n", cb0, cb1, cb2);

  return 0;
}

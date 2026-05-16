#include <malloc.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  void *a = sbrk(0);
  printf("a: %p\n", a);

  char *p = malloc(1024);
  void *b = sbrk(0);
  printf("b: %p\n", b);
  printf("diff: %ld kb\n", (b - a) / 1024);

  char *q = malloc(1024 * 66);
  char *r = malloc(1024 * 66);
  void *c = sbrk(0);
  printf("c: %p\n", c);
  printf("diff: %ld kb\n", (c - b) / 1024);
  free(r);
  void *d = sbrk(0);
  printf("d: %p\n", d);
  printf("diff: %ld kb\n", (d - a) / 1024);

  extern char end;
  void *e = &end;
  printf("tot: %ld kb\n", (d - e) / 1024);

  // void *d = sbrk(0);
  // printf("d: %p\n", d);
  // printf("diff: %ld kb\n", (d - c) / 1024);

  printf("pid: %d\n", getpid());
  while (1) {
  }
  return 0;
}

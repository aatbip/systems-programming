#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
  void *b0 = sbrk(0);
  sbrk(1024); // 1k
  void *b1 = sbrk(0);
  sbrk(1024); // 4k
  void *b2 = sbrk(0);
  sbrk(1024); // 4k
  void *b3 = sbrk(0);
  sbrk(1024); // 4k
  void *b4 = sbrk(0);
  printf("b0: %p\n", b0);
  printf("b1: %p\n", b1);
  printf("b2: %p\n", b2);
  printf("b3: %p\n", b3);
  printf("b4: %p\n", b4);

  return 0;
}

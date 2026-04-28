#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

jmp_buf env;

int x(char *a) {
  longjmp(env, atoi(a));
  printf("i should not run...\n");
  return 0;
}

int main(int argc, char *argv[]) {
  printf("executing x()\n");
  int n = setjmp(env);
  if (n == 0) {
    x(argv[1]);
  }
  if (n == 1) {
    printf("n is 1\n");
  }
  if (n == 2) {
    printf("n is 2\n");
  }
  return 0;
}

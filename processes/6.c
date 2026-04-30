#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
int main(void) {
  pid_t pid = fork();
  int ret;
  switch (pid) {
  case 0:
    printf("child\n");
    return 3;

  default:
    wait(&ret);
    break;
  }
  printf("parent: %d\n", ret >> 8);
  return 0;
}

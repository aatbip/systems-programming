#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void efunc(void) {
  printf("[%d]", getpid());
  printf("i am exit handler\n");
}

int main(void) {
  pid_t pid = fork();
  int ret;
  switch (pid) {
  case 0:
    printf("[%d] child\n", getpid());
    exit(2);
    break;

  default:
    wait(&ret);
    atexit(efunc);
    break;
  }
  printf("parent [%d]: %d\n", getpid(), ret >> 8);
  exit(EXIT_SUCCESS);
}

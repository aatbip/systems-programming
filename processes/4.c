#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
int main(void) {
  int status;
  switch (fork()) {
  case -1:
    exit(EXIT_FAILURE);
  case 0:
    printf("child running\n");
    sleep(1);
    printf("child complete\n");
    _exit(1);
    break;

  default:
    printf("parent running\n");
    wait(&status);
    printf("child status: %d\n", status);
    break;
  }
  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
int main(void) {
  switch (fork()) {
  case -1:
    exit(EXIT_FAILURE);
  case 0:
    printf("child running\n");
    sleep(1);
    printf("child complete\n");
    break;

  default:
    printf("parent running\n");
    // wait(NULL);
    break;
  }
  return 0;
}

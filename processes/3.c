#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  pid_t pid;
  int val = 11;
  pid = fork();
  int *n = malloc(sizeof(int));
  *n = 11;

  // switch (pid = fork()) {
  // case -1:
  //   perror("fork");
  //   exit(EXIT_FAILURE);
  //   break;
  //
  //   /*Child process*/
  // case 0:
  //   val = 22;
  //   break;
  //
  // default:
  //   break;
  // }

  /*Both parent and child*/
  *n = pid == 0 ? 22 : 33;
  int i = 0;
  while (i < 10) {
    printf("%s: %d\n", pid == 0 ? "child" : "parent", *n);
    if (pid != 0) {
      sleep(2);
    } else {
      sleep(1);
    }
    i++;
  }
  return 0;
}

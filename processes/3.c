#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  pid_t pid;
  int val = 11;
  pid = fork();

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
  val = pid == 0 ? 22 : 33;
  int i = 0;
  while (i < 10) {
    printf("%s: %d\n", pid == 0 ? "child" : "parent", val);
    if (pid != 0) {
      sleep(2);
    } else {
      sleep(1);
    }
    i++;
  }
  return 0;
}

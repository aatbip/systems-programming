#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  for (int i = 0; i < atoi(argv[1]); i++) {
    switch (fork()) {
    case -1:
      exit(EXIT_FAILURE);

    case 0:
      printf("child\n");
      _exit(EXIT_SUCCESS);

    default:
      printf("parent\n");
      wait(NULL);
      break;
    }
  }
  return 0;
}

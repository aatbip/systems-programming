#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  printf("Hello world\n");
  write(STDOUT_FILENO, "Ciao\n", 5);
  pid_t pid;
  if ((pid = fork()) == -1) {
    exit(EXIT_FAILURE);
  }
  exit(EXIT_SUCCESS);
}

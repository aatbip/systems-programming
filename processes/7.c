#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  printf("Hello world\n");
  write(STDOUT_FILENO, "Ciao\n", 5);
  setbuf(stdout, NULL);
  pid_t pid;
  if ((pid = fork()) == -1) {
    exit(EXIT_FAILURE);
  }
  if (pid == 0) {
    exit(1);
  }
  if (pid > 0) {
    int status;
    wait(&status);
    printf("status: %d\n", status >> 8);
  }
  exit(EXIT_SUCCESS);
}

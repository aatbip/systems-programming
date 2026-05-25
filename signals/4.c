/*Analyzing what may possibly happen when sending multiple signals to a process concurrently.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  int proc;
  switch ((proc = fork())) {
  case -1:
    perror("fork");
    exit(EXIT_FAILURE);

  // child process
  case 0:
    break;

  // parent process
  default:
    break;
  }
}

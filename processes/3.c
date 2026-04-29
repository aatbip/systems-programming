#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int fd1 = open("file1", O_CREAT | O_RDWR, 0700);
  int fd2 = open("file2", O_CREAT | O_RDWR, 0700);
  switch (fork()) {
  case -1:
    exit(EXIT_FAILURE);
    break;

  case 0:
    lseek(fd1, 100, SEEK_SET);
    break;

  default:
    wait(NULL);
    printf("%ld\n", lseek(fd1, 0, SEEK_CUR));
    break;
  }
  return 0;
}

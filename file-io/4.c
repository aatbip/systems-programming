#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int fd1 = open(argv[1], O_CREAT | O_RDWR, 0700);
  int fd2 = open(argv[2], O_CREAT | O_RDWR, 0700);
  printf("fd1: %d\n", fd1);
  printf("fd2: %d\n", fd2);
  write(fd1, "hello fd1", 9);
  write(fd2, "hello fd2", 9);
  lseek(fd1, 0, SEEK_SET);
  lseek(fd2, 0, SEEK_SET);

  char fd1_in[10], fd2_in[10];
  if ((read(fd1, fd1_in, 9)) == -1 || (read(fd2, fd2_in, 9)) == -1) {
    perror("read");
  }
  if ((write(STDOUT_FILENO, fd1_in, 9)) == -1 || (write(STDOUT_FILENO, fd2_in, 9)) == -1) {
    perror("write");
  }

  printf("after dup: \n");

  close(fd1);
  int new = dup(fd2);
  // int new = dup2(fd2, fd1);
  printf("new: %d\n", new);
  printf("fd1: %d\n", fd1);
  printf("fd2: %d\n", fd2);

  if ((pread(fd1, fd1_in, 9, 0)) == -1 || (pread(fd2, fd2_in, 9, 0)) == -1) {
    perror("read");
  }
  if ((write(STDOUT_FILENO, fd1_in, 9)) == -1 || (write(STDOUT_FILENO, fd2_in, 9)) == -1) {
    perror("write");
  }

  return 0;
}

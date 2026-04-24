#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int fd1 = open(argv[1], O_CREAT | O_RDWR, 0700);
  int fd2 = open(argv[1], O_CREAT | O_RDWR, 0700);
  printf("fd1: %d\t fd2: %d\n", fd1, fd2);
  write(fd1, "written by fd1 ", 16);
  lseek(fd2, 0, SEEK_END);
  write(fd2, "written by fd2 ", 16);
  // close(fd1);
  // printf("fd1 closed\n");
  // printf("fd1: %d\t fd2: %d\n", fd1, fd2);
  // close(fd2);
  // printf("fd2 closed\n");
  // printf("fd1: %d\t fd2: %d\n", fd1, fd2);
  return 0;
}

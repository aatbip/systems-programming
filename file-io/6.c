#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>

int main(void) {
  // int fd = open64("test.txt", O_CREAT | O_RDWR, 0700);
  // lseek64(fd, 10111222333, SEEK_SET);
  // write(fd, "test", 4);

  printf("PID: %d\n", getpid());
  sleep(5);
  int fd = open("test", O_CREAT | O_RDONLY, 0700);
  printf("fd: %d\n", fd);
  sleep(5);
  close(fd);
  sleep(5);
  return 0;
}

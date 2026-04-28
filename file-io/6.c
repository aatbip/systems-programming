#define _LARGEFILE64_SOURCE
// for large file access
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>

int main(void) {
  int fd = open64("test.txt", O_CREAT | O_RDWR, 0700);
  lseek64(fd, 10111222333, SEEK_SET);
  write(fd, "test", 4);
  return 0;
}

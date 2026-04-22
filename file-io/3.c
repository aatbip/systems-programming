#include <fcntl.h>
#include <stdio.h>

int main(void) {
  int fd = open("./test", O_CREAT | O_EXCL, 0700);
  if (fd == -1) {
    perror("open");
  }
  return 0;
}

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
  int i_fd = open("./test", O_RDONLY);
  int o_fd = open("./result", O_CREAT | O_RDWR, 0700);
  char *buf = malloc(32768 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2);
  int i = 0;
  while (read(i_fd, buf, 32768 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2) > 0) {
    i++;
    write(o_fd, buf, 32768 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2);
  }
  printf("syscalls: %d\n", i);
  return 0;
}

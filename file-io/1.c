#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) {
  mode_t mode = 0700;
  int o_fd = open("./test", O_CREAT | O_RDWR | O_APPEND, mode);
  char *buf = "hello world 123\0";
  if (write(o_fd, buf, strlen(buf)) == -1) {
    perror("write");
    exit(EXIT_FAILURE);
  }
  exit(EXIT_SUCCESS);
}

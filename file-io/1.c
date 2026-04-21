#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) {
  mode_t mode = 0700;
  // simple form of redirection by closing the stdout fd and open call will open the file with
  // lowest possible fd. Then printf will write to the file instead of writing to the stdout stream.
  if (close(STDOUT_FILENO) == -1) {
    perror("close");
  }
  int o_fd = open("./test", O_CREAT | O_RDWR | O_APPEND, mode);
  printf("o_fd: %d\n", o_fd);
  // char *buf = "hello world 123\0";
  // if (write(o_fd, buf, strlen(buf)) == -1) {
  //   perror("write");
  //   exit(EXIT_FAILURE);
  // }
  exit(EXIT_SUCCESS);
}

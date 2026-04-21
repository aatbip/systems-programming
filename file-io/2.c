#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
  int i_fd = open("./test", O_RDONLY);
  int o_fd = open("./result", O_CREAT | O_RDWR, 0700);
  char *buf = malloc(2);
  int i = 0;
  while (read(i_fd, buf, 2) > 0) {
    i++;
    write(o_fd, buf, 2);
  }
  printf("syscalls: %d\n", i);
  free(buf);

  // char input[16];
  // if (read(STDIN_FILENO, input, 16) == -1) {
  //   perror("read");
  // }
  // printf("input: %s\n", input);

  off_t cur = lseek(i_fd, 5, SEEK_SET);
  printf("cur: %ld\n", cur);
  char buf1[16];
  read(i_fd, buf1, 16);
  write(STDOUT_FILENO, buf1, 16);

  return 0;
}

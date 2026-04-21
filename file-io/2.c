#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
  int i_fd = open("./test", O_RDWR);
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

  off_t cur = lseek(i_fd, 2, SEEK_END);
  write(i_fd, "hey you", 7);
  off_t cur1 = lseek(i_fd, 0, SEEK_SET);
  char buf1[32];
  read(i_fd, buf1, 32);
  printf("cur1: %ld\n", cur1);
  printf("buf1: %s\n", buf1);

  return 0;
}

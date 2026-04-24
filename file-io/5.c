#include <bits/types/struct_iovec.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/uio.h>
#include <unistd.h>

int main(void) {
  int fd = open("file", O_RDONLY);
  struct ctrl {
    char type[6];
    char in[4];
  };
  struct ctrl c;
  char name[4];
  struct iovec iv[2];

  int req = 0;
  iv[0].iov_base = &c;
  iv[0].iov_len = sizeof(c);
  req += iv[0].iov_len;
  iv[1].iov_base = &name;
  iv[1].iov_len = 4;
  req += iv[1].iov_len;

  int numRead = readv(fd, iv, 2);

  c.type[5] = '\0';
  c.in[3] = '\0';
  name[3] = '\0';

  printf("type: %s\nin: %s\nname: %s\n", c.type, c.in, name);
  printf("numRead: %d\n", numRead);
  printf("req: %d\n", req);

  return 0;
}

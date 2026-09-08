#include <bits/sockaddr.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

int main(void) {
  int fd = socket(AF_UNIX, SOCK_STREAM, 0);
  printf("%d\n", fd);

  struct sockaddr *addr = malloc(sizeof(struct sockaddr));
  addr->sa_family = AF_INET;

  int c = bind(fd, addr, sizeof(*addr));

  return 0;
}

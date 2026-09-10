#include <asm-generic/errno-base.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main(void) {
  const char *PATH = "/tmp/sockunix";
  if (remove(PATH) == -1 && errno != ENOENT) {
    perror("remove");
    exit(EXIT_FAILURE);
  }

  int fd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (fd == -1) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_un addr;
  memset(&addr, 0, sizeof(struct sockaddr_un));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, PATH, strlen(PATH) - 1);

  if (bind(fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1) {
    perror("bind");
    exit(EXIT_FAILURE);
  }
}

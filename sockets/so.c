#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/un.h>

int main(void) {
  const char *PATH = "/tmp/sockunix";

  struct sockaddr_un addr;
  memset(&addr, 0, sizeof(struct sockaddr_un));

  addr.sun_family = AF_UNIX;
  strcpy(addr.sun_path, PATH);
  addr.sun_path[strlen(PATH) + 1] = '\0';

  int fd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (fd != 0) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  if (bind(fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) != 0) {
    perror("bind");
    exit(EXIT_FAILURE);
  }

  return 0;
}

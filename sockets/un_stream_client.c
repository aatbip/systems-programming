// Implementation of unix domain stream client socket

#include <asm-generic/errno-base.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define BACKLOG 5
#define BUF_SIZE 100
#define PATH "/tmp/sockunix"

int main(void) {
  int fd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (fd == -1) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_un addr;
  memset(&addr, 0, sizeof(struct sockaddr_un));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, PATH, sizeof(addr.sun_path) - 1);

  if (connect(fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1) {
    perror("connect");
    exit(EXIT_FAILURE);
  }
  int numread;
  int buf[BUF_SIZE];
  while ((numread = read(STDIN_FILENO, buf, BUF_SIZE)) > 0) {
    if (write(fd, buf, numread) != numread) {
      printf("partial or no write\n");
    }
    read(fd, buf, BUF_SIZE);
    write(STDOUT_FILENO, buf, numread);
  }
  if (numread == -1) {
    perror("read");
    exit(EXIT_FAILURE);
  }

  if (close(fd) == -1) {
    perror("close");
    exit(EXIT_FAILURE);
  }
}

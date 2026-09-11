#include <asm-generic/errno-base.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>

#define PATH "/tmp/dgram_server"
#define BUF_SIZE 10

int main(void) {
  int fd = socket(AF_UNIX, SOCK_DGRAM, 0);
  if (fd == -1) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_un s_addr;
  memset(&s_addr, 0, sizeof(struct sockaddr_un));
  s_addr.sun_family = AF_UNIX;
  strncpy(s_addr.sun_path, PATH, sizeof(s_addr.sun_path) - 1);

  if (remove(PATH) == -1 && errno != ENOENT) {
    perror("remove");
    exit(EXIT_FAILURE);
  }

  if (bind(fd, (struct sockaddr *)&s_addr, sizeof(struct sockaddr_un)) == -1) {
    perror("bind");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_un c_addr;
  int len = sizeof(struct sockaddr_un);
  char buf[BUF_SIZE];
  for (;;) {
    int recvbyte = recvfrom(fd, buf, BUF_SIZE, 0, (struct sockaddr *)&c_addr, (socklen_t *)&len);

    if (recvbyte == -1) {
      perror("recvfrom");
      exit(EXIT_FAILURE);
    }

    for (int i = 0; i < recvbyte; i++) {
      buf[i] = toupper((unsigned char)buf[i]);
    }

    if (sendto(fd, buf, recvbyte, 0, (struct sockaddr *)&c_addr, (socklen_t)len) < recvbyte) {
      printf("Failed to send from server\n");
    }
  }
}

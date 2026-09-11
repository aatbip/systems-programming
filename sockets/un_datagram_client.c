#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define PATH "/tmp/dgram_server"
#define BUF_SIZE 10

int main(void) {
  int fd = socket(AF_UNIX, SOCK_DGRAM, 0);
  if (fd == -1) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_un c_addr;
  memset(&c_addr, 0, sizeof(struct sockaddr_un));
  c_addr.sun_family = AF_UNIX;
  sprintf(c_addr.sun_path, "%s.%d", PATH, getpid());

  if (bind(fd, (struct sockaddr *)&c_addr, sizeof(struct sockaddr_un)) == -1) {
    perror("bind");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_un s_addr;
  memset(&s_addr, 0, sizeof(struct sockaddr_un));
  s_addr.sun_family = AF_UNIX;
  strncpy(s_addr.sun_path, PATH, sizeof(s_addr.sun_path) - 1);

  char buf[BUF_SIZE];
  for (;;) {
    int numread;
    if ((numread = read(STDIN_FILENO, buf, BUF_SIZE)) == -1) {
      perror("read");
      exit(EXIT_FAILURE);
    }
    if (sendto(fd, buf, numread, 0, (struct sockaddr *)&s_addr, (socklen_t)sizeof(struct sockaddr_un)) == -1) {
      printf("Failed to send by client\n");
    }

    int recvbyte = recvfrom(fd, buf, BUF_SIZE, 0, NULL, NULL);
    if (recvbyte == -1) {
      perror("recvfrom");
      exit(EXIT_FAILURE);
    }
    buf[recvbyte] = '\0';

    printf("received: %s", buf);
  }
}

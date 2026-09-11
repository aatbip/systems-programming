// Implementation of unix domain stream server socket

#include <asm-generic/errno-base.h>
#include <errno.h>
#include <pthread.h>
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

void *server_run(void *arg) {
  int sfd = (int)(ptrdiff_t)arg;
  int numread;
  char buf[BUF_SIZE];
  while (((numread = read(sfd, buf, BUF_SIZE)) > 0)) {
    if (write(STDOUT_FILENO, buf, numread) != numread) {
      printf("Partial or no write\n");
    }
  }
  if (numread == -1) {
    perror("read");
    exit(EXIT_FAILURE);
  }

  if (close(sfd) == -1) {
    perror("close");
    exit(EXIT_FAILURE);
  }
  return NULL;
}

int main(void) {
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
  strncpy(addr.sun_path, PATH, sizeof(addr.sun_path) - 1);

  if (bind(fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1) {
    perror("bind");
    exit(EXIT_FAILURE);
  }

  if (listen(fd, BACKLOG) == -1) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  for (;;) {
    int sfd = accept(fd, NULL, NULL);
    if (sfd == -1) {
      perror("accept");
      exit(EXIT_FAILURE);
    }

    pthread_t th;
    pthread_create(&th, NULL, server_run, (void *)(ptrdiff_t)sfd);
  }
}

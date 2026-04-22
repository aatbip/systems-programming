#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
  int fd;
  if ((fd = open("test", O_CREAT | O_RDWR, 0700)) == -1) {
    perror("open");
    exit(EXIT_FAILURE);
  }
  if (lseek(fd, 0, SEEK_END) == -1) {
    perror(("lseek"));
    exit(EXIT_FAILURE);
  }
  if (argc > 2) {
    printf("sleeping...\n");
    sleep(20);
  }
  if (write(fd, argv[1], strlen(argv[1])) < strlen(argv[1])) {
    char *err = "err: partial or no write";
    write(STDERR_FILENO, err, strlen(err));
    exit(EXIT_FAILURE);
  }
  exit(EXIT_SUCCESS);
}

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void err_exit(char *err_txt) {
  write(STDERR_FILENO, err_txt, strlen(err_txt));
  exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
  if (argc < 2) {
    err_exit("Missing arg");
  }
  char *file_name = argv[1];
  char *dest = malloc(strlen(file_name) + 3);
  strcpy(dest, "./");
  strcat(dest, file_name);
  int fd;
  if ((fd = open(dest, O_CREAT | O_WRONLY | O_APPEND, 0700)) == -1) {
    perror("open");
    exit(EXIT_FAILURE);
  }
  char in_buf[1024];
  int read_count;
  while ((read_count = read(STDIN_FILENO, in_buf, 1024)) > 0) {
    if (write(fd, in_buf, read_count) == -1 || write(STDOUT_FILENO, in_buf, read_count) == -1) {
      perror("write");
      exit(EXIT_FAILURE);
    }
  }
  exit(EXIT_SUCCESS);
}

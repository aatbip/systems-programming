#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
  int fd = open(argv[1], O_RDWR);
  if (fd != -1) {
    printf("[PID: %d] File \"%s\" already exists.\n", getpid(), argv[1]);
  } else {
    if (argc > 2) {
      printf("[PID: %d] Sleeping...\n", getpid());
      sleep(10);
    }
    int fd = open(argv[1], O_CREAT | O_RDWR, 0700);
    if (fd == -1) {
      perror("open");
    }
    printf("[PID: %d] Created the file \"%s\"\n", getpid(), argv[1]);
  }
  return 0;
}

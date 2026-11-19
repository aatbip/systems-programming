#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define ERR write(STDOUT_FILENO, "err\n", 4);

int main(void) {
  int fd = open("test_file", O_RDWR);
  if (fd == -1)
    ERR;

  struct stat s;
  if (fstat(fd, &s) == -1) {
    ERR;
  }

  void *p = mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

  if (p == MAP_FAILED)
    ERR;

  if (write(STDOUT_FILENO, p, s.st_size) != s.st_size)
    ERR;

  exit(EXIT_SUCCESS);
}

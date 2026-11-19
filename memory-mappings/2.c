// This program demonstrates shared anonymous mapping between parent and child process

#include <fcntl.h>
#include <stdio.h>
#ifdef USE_MAP_ANON
#define DEFAULT_SOURCE
#endif
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

#define ERR                                                                                                            \
  do {                                                                                                                 \
    write(STDOUT_FILENO, "err\n", 4);                                                                                  \
    exit(EXIT_FAILURE);                                                                                                \
  } while (0)

int main(void) {
  int *p;
#ifdef USE_MAP_ANON
  p = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  if (p == MAP_FAILED)
    ERR;
  printf("its usemap\n");
#else
  int fd = open("/dev/zero", O_RDWR);
  if (fd == -1)
    ERR;
  p = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (p == MAP_FAILED)
    ERR;
  if (close(fd) == -1)
    ERR;
  printf("its dev zero\n");
#endif

  *p = 1;
  printf("from parent: %d\n", *p);

  int c = fork();

  if (c == -1)
    ERR;
  if (c == 0) {
    *p += 1;
    printf("from child: %d\n", *p);
    exit(EXIT_SUCCESS);
  }
  wait(NULL);

  if (munmap(p, sizeof(*p)) == -1)
    ERR;

  exit(EXIT_SUCCESS);
}

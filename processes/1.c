#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
  printf("[%d] process running\n", getpid());
  char buf[4];
  for (int i = 0; i < 1000; i++) {
    int len = snprintf(buf, sizeof(buf), "%d ", i);
    write(STDOUT_FILENO, buf, len);
    sleep(1);
  }
  return 0;
}

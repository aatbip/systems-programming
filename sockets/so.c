#include <stdio.h>
#include <sys/socket.h>

int main(void) {
  int s = socket(AF_UNIX, SOCK_STREAM, 0);
  printf("%d\n", s);

  return 0;
}

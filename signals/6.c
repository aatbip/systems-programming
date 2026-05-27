#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

void handler(int sig) {
  struct timeval tv;
  struct timezone tz;
  int i = gettimeofday(&tv, &tz);
  printf("fired\n");
  sleep(5);
  printf("time %ld\n", tv.tv_sec);
}

int main(void) {
  printf("pid: %d\n", getpid());
  struct sigaction act;
  act.sa_handler = handler;
  // act.sa_flags = SA_NODEFER;
  if (sigaction(SIGTERM, &act, NULL) == -1) {
    perror("sigaction");
  }

  // if (signal(SIGTERM, handler) == SIG_ERR) {
  //   perror("signal");
  // }

  for (;;)
    pause();
  exit(EXIT_SUCCESS);
}

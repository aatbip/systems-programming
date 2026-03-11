#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *worker(void *arg) {
  printf("worker thread\n");
  int *i = malloc(sizeof(*i));
  return i;
}

int main(void) {
  pthread_t *th = malloc(sizeof(*th));
  int ret = pthread_create(th, NULL, worker, NULL);
  /*Traditional syscall functions and other library functions return 0 on success and -1 on failure.
   * pthread functions returns 0 on succces and non negative numbers on failure that indicates the
   * error message.*/
  if (ret != 0) {
    printf("err: %s\n", strerror(ret));
  }
  printf("main thread\n");
  return 0;
}

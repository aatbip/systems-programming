#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *worker(void *arg) {
  printf("worker thread\n");
  int *i = malloc(sizeof(*i));
  return i;
}

int main(void) {
  pthread_t *th = malloc(sizeof(*th));
  pthread_create(th, NULL, worker, NULL);
  printf("main thread\n");
  return 0;
}

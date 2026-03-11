/*In this program:
 **/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *worker(void *arg) {
  printf("worker thread\n");
  int *i = malloc(sizeof(*i));
  *i = 77;
  /*Thread can be terminated using pthread_exit. `retval` can be passed as argument that can be
   * caught in pthread_join*/
  pthread_exit(i);
  printf("after termination\n");
}

int main(void) {
  pthread_t *th = malloc(sizeof(*th));
  int ret = pthread_create(th, NULL, worker, NULL);
  if (ret != 0) {
    printf("err: %s\n", strerror(ret));
  }
  int *i;
  pthread_join(*th, (void **)&i);
  printf("main thread, ret val: %d\n", *i);
  return 0;
}

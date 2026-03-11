/*In this program:
 * - Creating thread using pthread_create
 * - Waiting for worker thread to return using pthread_join
 * - Catching error from pthread functions
 **/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *worker(void *arg) {
  printf("worker thread\n");
  int *i = malloc(sizeof(*i));
  *i = 77;
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
  int *i;
  /*pthread_join waits for the thread with `th` thread id to return before continuing. It blocks the
   * caller thread (main in this case) until the worker thread returns. It also cleans up the resources
   * such as the stack (thread local storage), thread file descriptors, and others. It also gives
   * access to the return value of the `worker`.*/
  pthread_join(*th, (void **)&i);
  printf("main thread. Return val: %d\n", *i);
  return 0;
}

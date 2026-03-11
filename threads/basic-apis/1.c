/*In this program:
 * - Working with thread ids
 * - Terminating the thread using thread_exit
 * - Detaching the thread using pthread_detach
 **/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *worker(void *arg) {
  printf("worker thread: %ld\n", pthread_self());
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
  /*pthread_t is of type unsigned long in Linux and it stores the thread id.*/
  printf("thread id: %ld\n", *th);
  if (ret != 0) {
    printf("err: %s\n", strerror(ret));
  }
  // int *i;
  // pthread_join(*th, (void **)&i);
  // printf("main thread, ret val: %d\n", *i);

  /*pthread_detach detaches the worker thread from caller thread. It means, caller thread doesn't wait for it
   * to terminate. The worker thread will auto clean itself. We can use pthread_exit in the main thread to
   * terminate the main thread but still keep the process alive so that worker thread will still keep on
   * running.*/
  pthread_detach(*th);
  pthread_exit(NULL);
  return 0;
}

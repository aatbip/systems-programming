/*This program shows how to allocate thread specific data.*/

#define _GNU_SOURCE
#include <asm-generic/errno-base.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ERROR_LEN 256
struct buf {
  char *b;
};

char *strerror1(int err) {
  static __thread struct buf *b = NULL;

  if (!b) {
    b = malloc(sizeof(struct buf));
    b->b = malloc(MAX_ERROR_LEN);
  }
  char *buf = b->b;

  if (err < 0) {
    snprintf(buf, MAX_ERROR_LEN, "Unknown error %d", err);
  } else {
    strncpy(buf, strerror(err), MAX_ERROR_LEN - 1);
    buf[MAX_ERROR_LEN - 1] = '\0';
  }
  return buf;
}

void *func(void *p) {
  char *s;
  printf("strerr will be called from func\n");
  s = strerror1(EPERM);
  printf("from func: %s\n", s);
  return NULL;
}

int main(void) {
  char *s;
  s = strerror1(EINVAL);
  printf("strerr called from main\n");

  pthread_t th;
  pthread_create(&th, NULL, func, NULL);
  pthread_join(th, NULL);

  printf("from main: %s\n", s);

  return 0;
}

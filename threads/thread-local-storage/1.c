/*This program shows how to allocate thread specific data.*/

#define _GNU_SOURCE
#include <asm-generic/errno-base.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ERROR_LEN 256
static pthread_once_t once = PTHREAD_ONCE_INIT;
static pthread_key_t key;

static void clean(void *buf) { free(buf); }

static void create_key(void) { pthread_key_create(&key, clean); }

char *strerror1(int err) {
  char *buf;
  int s = pthread_once(&once, create_key);
  if (s != 0) {
    perror("pthread_once\n");
  }

  buf = pthread_getspecific(key);
  if (!buf) {
    buf = malloc(MAX_ERROR_LEN); // 256 byte max buffer size
    if (!buf) {
      perror("malloc\n");
    }
    pthread_setspecific(key, buf);
  }

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

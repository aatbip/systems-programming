#define _GNU_SOURCE
#include <asm-generic/errno-base.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ERROR_LEN 256

typedef struct {
  char buf[MAX_ERROR_LEN];
} thread_buf_t;

static __thread thread_buf_t *tl_buf = NULL;
static pthread_key_t tl_buf_key;
static pthread_once_t key_once = PTHREAD_ONCE_INIT;

static void thread_buf_destroy(void *ptr) {
  free(ptr);
  tl_buf = NULL;
}

static void create_key(void) { pthread_key_create(&tl_buf_key, thread_buf_destroy); }

thread_buf_t *thread_buf_init(void) {
  pthread_once(&key_once, create_key);

  thread_buf_t *b = malloc(sizeof(thread_buf_t));
  if (!b) {
    fprintf(stderr, "thread_buf_init: malloc failed\n");
    exit(1);
  }
  b->buf[0] = '\0';

  pthread_setspecific(tl_buf_key, b); // register for destructor on thread exit
  return b;
}

static inline thread_buf_t *get_thread_buf(void) {
  if (__builtin_expect(tl_buf == NULL, 0))
    tl_buf = thread_buf_init();
  return tl_buf;
}

char *strerror1(int err) {
  thread_buf_t *b = get_thread_buf();

  if (err < 0) {
    snprintf(b->buf, MAX_ERROR_LEN, "Unknown error %d", err);
  } else {
    strncpy(b->buf, strerror(err), MAX_ERROR_LEN - 1);
    b->buf[MAX_ERROR_LEN - 1] = '\0';
  }
  return b->buf;
}

void *func(void *p) {
  char *s;
  printf("strerr will be called from func\n");
  s = strerror1(EPERM);
  printf("from func: %s\n", s);
  return NULL; // thread_buf_destroy fires here for this thread
}

int main(void) {
  char *s;
  s = strerror1(EINVAL);
  printf("strerr called from main\n");

  pthread_t th;
  pthread_create(&th, NULL, func, NULL);
  pthread_join(th, NULL);

  printf("from main: %s\n", s);

  // main thread cleanup — pthread destructor doesn't fire for main on return,
  // so free explicitly (mirrors mi_heap_done() called in atexit handler)
  free(tl_buf);
  tl_buf = NULL;

  return 0;
}

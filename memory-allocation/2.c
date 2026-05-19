#include <malloc.h>
#include <setjmp.h>
#include <stdio.h>
struct t {
  int rt;
  int *n;
};

int foo(jmp_buf *buf) {
  struct t *p = malloc(sizeof(struct t));
  p->rt = 1;
  p->n = malloc(sizeof(int));
  *(p->n) = 21;
  printf("in foo\n");
  longjmp(*buf, (long)(void *)p);
  return 0;
}

int main(void) {
  struct t *p = malloc(sizeof(struct t));
  jmp_buf buf;
  long f = setjmp(buf);
  struct t *res = ((struct t *)f);
  if (f == 0) {
    foo(&buf);
  }
  if (res->rt == 1) {
    printf("res n: %d\n", *res->n);
    printf("returning from main\n");
  }
  free(res->n);
  free(res);
  return 0;
}

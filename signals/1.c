#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
  int a = 1;
  // exit with core dump
  abort();
}

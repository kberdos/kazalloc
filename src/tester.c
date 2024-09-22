#include "kazalloc.h"
#include <stdio.h>

int main(int arc, char **argv) {
  printf("Hello from the tester!\n");
  // Make a call to kazalloc
  void *p = kazalloc(0);
  return 0;
}

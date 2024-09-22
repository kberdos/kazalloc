#include "kazalloc.h"
#include <stdio.h>

void run_malloc_test() {
  printf("Hello world!\n");
  // Make a call to kazalloc's malloc!!
  int *iptr_1 = malloc(sizeof(int));
  *iptr_1 = 5;
  printf("The value of int 1 is %d\n", *iptr_1);
  free(iptr_1);

  // Shenanigans!
  // request a block of the same size, it should gives us the free one
  int *iptr_2 = malloc(sizeof(int));
  printf("The value of int 2 is %d\n", *iptr_2);
}

int main(int arc, char **argv) {
  run_malloc_test();
  return 0;
}

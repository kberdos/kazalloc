#include "kazalloc.h"
#include <stdio.h>

void run_malloc_test() {
  printf("Hello world!\n");
  // Make a call to kazalloc's malloc!!
  int *int_ptr = malloc(sizeof(int));
  *int_ptr = 5;
  // printf("The second value of the int is %d\n", *int_ptr);
  // free(int_ptr);
}

int main(int arc, char **argv) {
  run_malloc_test();
  return 0;
}

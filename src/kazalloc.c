#include <assert.h>
#include <stdio.h>
#include <unistd.h>

void *kazalloc(size_t size) {
  void *p = sbrk(0);
  void *request = sbrk(size);
  if (request == (void *)-1) {
    return NULL; // sbrk failed
  } else {
    // NOTE: not thread safe
    assert(p == request);
    return p;
  }
}

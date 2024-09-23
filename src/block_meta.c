#include "block_meta.h"
#include "stdio.h"
#include <assert.h>

/**
Attempts to find a free block in the heap of sufficient size.
- last: keep a reference to the "top" block pointer of the heap. Calling this
function will set the last pointer properly.
- size: desired heap block size
*/

// get the metadata associated with an address
t_block get_t_block(void *addr) { return (t_block)addr - 1; }

struct block_meta *find_free_block(void *global_base, t_block *last_ptr,
                                   size_t size) {
  // start from the global base
  t_block current = global_base;
  while (current && !(current->free && current->size >= size)) {
    *last_ptr = current;
    current = current->next;
  }
  return current;
}

/**
Request a new block of heap memory of the proper size. Returns NULL if failure
- last: pointer to the last block in the heap
*/
t_block request_space(void *global_base, t_block last, size_t size) {
  t_block block;
  block = sbrk(0);
  // Try to move the program break by size bytes
  void *request = sbrk(size + META_SIZE);
  // assert that it actually moved it over (NOT thread safe)
  assert((void *)block == request);
  if (request == (void *)-1) {
    return NULL;
  }
  // last is NULL on the first request
  if (last) {
    // our new block is now the last block
    last->next = block;
  }
  block->next = NULL;
  block->free = 0;
  block->size = size;
  return block;
}

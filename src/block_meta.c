#include "block_meta.h"
#include "stdio.h"

/**
Attempts to find a free block in the heap of sufficient size.
- last: keep a reference to the "top" block pointer of the heap. Calling this
function will set the last pointer properly.
- size: desired heap block size
*/

// get the metadata associated with an address
struct block_meta *get_block_meta(void *addr) {
  return (struct block_meta *)addr - 1;
}

struct block_meta *find_free_block(void *global_base, struct block_meta **last,
                                   size_t size) {
  // start from the global base
  struct block_meta *current = global_base;
  while (current && !(current->free && current->size >= size)) {
    *last = current;
    current = current->next;
  }
  return current;
}

/**
Request a new block of heap memory of the proper size. Returns NULL if failure
- last: pointer to the last block in the heap
*/
struct block_meta *request_space(void *global_base, struct block_meta *last,
                                 size_t size) {
  struct block_meta *block;
  // Try to move the program break by size bytes
  void *request = sbrk(size);
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
  block->magic = 0x12345678;
  return block;
}

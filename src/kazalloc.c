#include "block_meta.h"
#include <assert.h>
#include <stdio.h>
#include <unistd.h>

// start off the global base at the nullpointer (0)
void *global_base = NULL;

void *malloc(size_t size) {
  // handle invalid size request
  if (size <= 0) {
    return NULL;
  }
  // On the first call, request new space
  struct block_meta *block;
  if (!global_base) {
    block = request_space(global_base, global_base, size);
    if (!block) {
      return NULL;
    }
    // now the base is this first block
    global_base = block;
  } else {
    struct block_meta *last = global_base;
    block = find_free_block(global_base, &last, size);
    if (!block) {
      // no free block found, so let's request more space
      block = request_space(global_base, last, size);
      if (!block) {
        return NULL;
      }
    } else {
      // nice! free block found. Let's update its metadata
      // TODO: consider splitting the block.
      block->free = 0;
      block->magic = 0x77777777;
    }
  }
  // return the address to the actual heap payload; which begins after the
  // metadata block
  return (block + 1);
}

/**
Frees the memory pointed to by ptr
*/
void free(void *ptr) {
  // don't do anything if the ptr is null
  if (!ptr) {
    return;
  }
  // get the associated block
  struct block_meta *block = get_block_meta(ptr);
  // ensure that the block is actually being used
  assert(block->free == 0);
  // for testing purposes
  assert(block->magic == 0x77777777 || block->magic == 0x12345678);
  // mark the block as free
  block->free = 1;
  // mark the block for testing
  block->magic = 0x55555555;
}

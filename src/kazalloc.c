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
  t_block block;
  if (!global_base) {
    block = request_space(global_base, global_base, size);
    if (!block) {
      return NULL;
    }
    // now the base is this first block
    global_base = block;
  } else {
    t_block last = global_base;
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
  t_block block = get_t_block(ptr);
  // ensure that the block is actually being used
  assert(block->free == 0);
  // mark the block as free
  block->free = 1;
}

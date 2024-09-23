#include "block_meta.h"
#include <assert.h>
#include <stdio.h>
#include <unistd.h>

// head of the linked list of free allocations
void *list_head = NULL;

void *malloc(size_t size) {
  // handle invalid size request
  if (size <= 0) {
    return NULL;
  }
  // On the first call, request new space
  t_block block;
  if (!list_head) {
    block = request_space(list_head, list_head, size);
    if (!block) {
      return NULL;
    }
    // now the base is this first block
    list_head = block;
  } else {
    t_block last = list_head;
    block = find_free_block(list_head, &last, size);
    if (!block) {
      // no free block found, so let's request more space
      block = request_space(list_head, last, size);
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

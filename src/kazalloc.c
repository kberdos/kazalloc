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
    list_head = block;
  } else {
    t_block list_tail = list_head;
    block = find_free_block(list_head, &list_tail, size);
    if (!block) {
      // no free block found, so let's request more space
      block = request_space(list_head, list_tail, size);
      if (!block) {
        return NULL;
      }
    } else {
      // nice! free block found. Let's update its metadata
      block->free = 0;
      try_split_block(block, size);
    }
  }
  return (block + 1); // return address after metadata
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
  // Attempt to the fuse the block with its neighbors
  block = fuse_right(block);
  if (block->prev && block->prev->free) {
    block = fuse_right(block->prev);
  }
}

/**
Print the internal representation of the heap allocations
*/
void print_state() {
  // start from the head, toString each block you hit until you reach the end
  t_block cursor = (t_block)list_head;
  printf("---------PRINTING STATE---------\n");
  while (cursor) {
    block_to_string(cursor);
    cursor = cursor->next;
    printf("\n");
  }
}

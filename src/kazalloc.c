#include "block_meta.h"
#include <assert.h>
#include <stdio.h>
#include <unistd.h>

// head of the linked list of free allocations
void *list_head = NULL;

void *malloc(size_t size) {
  if (size <= 0) {
    return NULL;
  }

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
      block = request_space(list_head, list_tail, size);
      if (!block) {
        return NULL;
      }
    } else {
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
  if (!ptr) {
    return;
  }
  t_block block = get_t_block(ptr);
  assert(block->free == 0);
  block->free = 1;
  block = fuse_right(block);
  if (block->prev && block->prev->free) {
    block = fuse_right(block->prev);
  }
}

void *realloc(void *ptr, size_t size) {
  // TODO: implement
  return NULL;
}

/**
Print the internal representation of the heap allocations
*/
void print_state() {
  t_block cursor = (t_block)list_head;
  printf("---------PRINTING STATE---------\n");
  while (cursor) {
    block_to_string(cursor);
    cursor = cursor->next;
    printf("\n");
  }
}

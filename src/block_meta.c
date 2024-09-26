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

/**
Look through the linked list of blocks for a free block of sufficient size.
Returns a valid block if found, null otherwise
Calling find_free_block sets last_ptr to the last block in the linked list
*/
t_block find_free_block(void *list_head, t_block *last_ptr, size_t size) {
  // start from the list head
  t_block current = list_head;
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
t_block request_space(void *list_head, t_block last, size_t size) {
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

/**
Attempts to split a block (must be big enough for a new header)
- desired_size: the desired size to be allocated in the original block (which is
at most the block's current size)
| META_SIZE | desired_size | META_SIZE | new_size BYTES |
*/
void try_split_block(t_block block, size_t desired_size) {
  // Prevent splits with insufficient size
  if (block->size < desired_size + META_SIZE + MIN_SPLIT_SIZE) {
    return;
  }
  size_t split_size = block->size - (desired_size + META_SIZE);
  // construct a new block with pointer arith.
  t_block split_block = block + META_SIZE + desired_size;
  split_block->size = split_size;
  split_block->free = 1;
  split_block->next = block->next;
  block->next = split_block;
  block->size = desired_size;
}

/**
Prints metadata and data within a block to stdout.
*/
void block_to_string(t_block block) {
  printf("BLOCK AT %p:\n", block);
  printf("- FREE %d:\n", block->free);
  printf("- SIZE %zu:\n", block->size);
  printf("- DATA: ");
  for (int i = 0; i < block->size; i++) {
    char b = *((char *)(block + 1) + i);
    // Collapse empty bytes into '.'
    if (!b) {
      printf(".");
    } else {
      printf("0x%02x", b);
    }
  }
  printf("\n");
}

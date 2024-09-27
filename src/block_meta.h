#ifndef BLOCK_META_
#define BLOCK_META_
#include <sys/types.h>
#include <unistd.h>

// A meta block is always referred to by a pointer
typedef struct block_meta *t_block;

struct block_meta {
  size_t size;  // 8 bytes
  t_block next; // 8 bytes
  t_block prev; // 8 bytes
  int free;     // 4 bytes
};

#define META_SIZE sizeof(struct block_meta)

#define MIN_SPLIT_SIZE 4 // min size of a newly-split block

t_block find_free_block(void *list_head, t_block *last_ptr, size_t size);
t_block request_space(void *list_head, t_block last, size_t size);

t_block get_t_block(void *addr);

void try_split_block(t_block block, size_t size);

t_block fuse_right(t_block block);

void block_to_string(t_block block);

#endif

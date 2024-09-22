#ifndef BLOCK_META_
#define BLOCK_META_
#include <sys/types.h>
#include <unistd.h>

struct block_meta {
  size_t size;
  struct block_meta *next;
  int free;
  int magic;
};

#define META_SIZE sizeof(struct block_meta)

struct block_meta *find_free_block(void *global_base, struct block_meta **last,
                                   size_t size);
struct block_meta *request_space(void *global_base, struct block_meta *last,
                                 size_t size);

struct block_meta *get_block_meta(void *addr);

#endif

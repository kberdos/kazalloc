#ifndef KAZALLOC_H_ /* Include guard */
#define KAZALLOC_H_

#include <sys/types.h>

void *malloc(size_t size);

void free(void *ptr);

void *realloc(void *ptr, size_t size);

void print_state();

#endif

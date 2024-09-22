#ifndef KAZALLOC_H_ /* Include guard */
#define KAZALLOC_H_

#include <sys/types.h>

void *malloc(size_t size);

void free(void *ptr);

#endif

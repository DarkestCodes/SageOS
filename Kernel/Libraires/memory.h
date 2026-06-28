#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>

void *kmalloc(size_t size);
void kfree(void *ptr);
void kinit_memory();


#endif
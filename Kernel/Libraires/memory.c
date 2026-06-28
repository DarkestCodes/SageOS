#include "memory.h"

#include "../Headers/Kernel.h"

#include <stddef.h>
#include <stdbool.h>

#define MEM_SIZE 4096
#define MIN_BLOCK_SIZE 16
#define BLOCK_MAGIC 0xCAFEBABE

static unsigned char mem_pool[MEM_SIZE] __attribute__((aligned(16)));

typedef struct Block {
    size_t size;
    bool is_free;
    unsigned int magic;
    struct Block *next;
} Block;

static Block *heap_start = NULL;

size_t align(size_t size) {
    return (size + 15) & ~15;
}

void heap_check()
{
    Block *current = heap_start;

    while(current)
    {
        if(current->magic != BLOCK_MAGIC)
            kernel_panic("HEAP CORRUPTION");

        current=current->next;
    }
}


void kinit_memory() {
    heap_start = (Block *)mem_pool;

    heap_start->size = MEM_SIZE - sizeof(Block);
    heap_start->is_free = true;
    heap_start->magic = BLOCK_MAGIC;
    heap_start->next = NULL;
}

void Split_Block(Block *block, size_t size) {

    size_t remaining = block->size - size;

    if (remaining <= sizeof(Block) + MIN_BLOCK_SIZE)
        return;


    Block *new_block =
        (Block *)((char *)block + sizeof(Block) + size);


    new_block->size = remaining - sizeof(Block);
    new_block->is_free = true;
    new_block->magic = BLOCK_MAGIC;
    new_block->next = block->next;


    block->size = size;
    block->next = new_block;
}

void Merge_Block() {
    Block *current = heap_start;
    
    while (current&& current->next) {
        
        Block *next = current->next;

        if (current->magic == BLOCK_MAGIC && next->magic == BLOCK_MAGIC && current->is_free && next->is_free) {
            
            current->size += sizeof(Block) + next->size;

            current->next = next->next;
            continue;
        }
        current = current->next;
    } 
}

void* kmalloc(size_t size) {
    heap_check();

    if (heap_start == NULL) return NULL;
    if (size == 0) return NULL;

    
    size = align(size);

    Block *current = heap_start;

    while (current) {
        if (current->magic == BLOCK_MAGIC && current->is_free && current->size >= size) {
            Split_Block(current, size);
            current->is_free = false;
            return (void *)(current + 1);
        }
        current=current->next;
    }
    return NULL;
}

void kfree(void *ptr) {
    heap_check();
    if (ptr == NULL)
        return;


    if ((unsigned char *)ptr < mem_pool || (unsigned char *)ptr >= mem_pool + MEM_SIZE)
        return;


    Block *header = (Block *)ptr - 1;


    if (header->magic != BLOCK_MAGIC)
        return;


    if (header->is_free)
        return;


    header->is_free = true;

    Merge_Block();
}


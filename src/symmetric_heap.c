/* -*- C -*-
 *
 * Copyright (c) 2011 Sandia National Laboratories. All rights reserved.
 */

#include "config.h"

#include <portals4.h>
#include <stdlib.h>
#include <stdio.h>

#include "mpp/shmem.h"
#include "shmem_internal.h"

long malloc_error = 0;

void *shmem_heap_base = NULL;
long shmem_heap_length = 0;
char *shmem_heap_curr = NULL;

void* shmem_get_next(int incr);
void* dlmalloc(size_t);
void  dlfree(void*);
void* dlrealloc(void*, size_t);
void* dlmemalign(size_t, size_t);

void*
shmem_get_next(int incr)
{
    char *orig = shmem_heap_curr;
    shmem_heap_curr += (incr > 0) ? incr : 0;
    if (shmem_heap_curr - (char*) shmem_heap_base > shmem_heap_length) {
        printf("WARNING: top of symmetric heap found\n");
        return (void*) -1;
    }
    return orig;
}

int
symmetric_init(void)
{
    long req_len = 64 * 1024 * 1024;
    char *env = getenv("SHMEM_SYMMETRIC_HEAP_SIZE");
    if (NULL != env) req_len = atoi(env);

    shmem_heap_length = req_len;
    shmem_heap_base = shmem_heap_curr = malloc(shmem_heap_length);
    if (NULL == shmem_heap_base)  return -1;

    return 0;
}

void *
shmalloc(size_t size)
{
    return dlmalloc(size);
}


void
shfree(void *ptr)
{
    dlfree(ptr);
}


void *
shrealloc(void *ptr, size_t size)
{
    return dlrealloc(ptr, size);
}


void *
shmemalign(size_t alignment, size_t size)
{
    return dlmemalign(alignment, size);
}
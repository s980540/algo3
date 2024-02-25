#ifndef UTILITY_H
#define UTILITY_H

#include "global.h"

void *aligned_alloc(size_t size, u32 align);
void aligned_free(void *aligned_ptr);

#define DBGPRINT(filter, ...) \
    printf(__VA_ARGS__)

#endif // ~ UTILITY_H

#ifndef UTILITY_H
#define UTILITY_H

#include "global.h"

#define DBGPRINT(filter, ...) \
    printf(__VA_ARGS__)

void print_platform_info(void);
#ifdef WIN32
extern void *aligned_alloc(size_t size, u32 align);
extern void aligned_free(void *aligned_ptr);
#endif
extern unsigned long get_num(const char *str);
extern void print_buf(const void *buf, size_t size, const char *title, ...);
extern size_t strlen(const char *s);

#endif // ~ UTILITY_H

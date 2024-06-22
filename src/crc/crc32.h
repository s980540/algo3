#ifndef CRC32_H
#define CRC32_H

#include "global.h"

#define CRC_LE_BITS                     (1)

// CRC-32C (Castagnoli)
#define POLY                            (0x1EDC6F41L)
/* CRC32C polynomial in reversed bit order. */
#define REVERSED_POLY                   (0x82F63b78L)

#define CRC_INIT                        (0xffffffffL)
#define XO_ROT                          (0xffffffffL)

u32 crc32(u32 crc, const void *buf, size_t len);
u32 crc32_tableless2(u32 crc, const void *buf, size_t len, u32 poly);
u32 crc32_tableless3(u32 crc, const void *buf, size_t len, u32 poly);
u32 crc32_halfbyte(u32 crc, const void *buf, size_t len);
u32 crc32_le_generic(u32 crc, const void *buf, size_t len, u32 poly);

void half_byte_table_generator(void);

#endif // ~ CRC32_H
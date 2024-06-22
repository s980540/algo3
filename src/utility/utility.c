#include "utility.h"

#include <limits.h>

#ifdef WIN32
void *aligned_alloc(size_t size, u32 align)
{
	size_t addr;
	void *ptr, *aligned_ptr;

	ptr = malloc(size + align + sizeof(size_t));
	if (ptr != NULL) {
		addr        = (size_t)ptr + align + sizeof(size_t);
		aligned_ptr = (void *)(addr - (addr % align));
		*((size_t *)aligned_ptr - 1) = (size_t)ptr;
		// printf("[%s](%x,%x)\n", __FUNCTION__, ptr, aligned_ptr);
	} else {
		return NULL;
	}

	return aligned_ptr;
}

void aligned_free(void *aligned_ptr)
{
	// printf("[%s](%x,%x)\n", __FUNCTION__, *((size_t *)aligned_ptr - 1), aligned_ptr);
	free((void *)(*((size_t *)aligned_ptr - 1)));
}
#endif

unsigned long get_num(const char *str)
{
	char *end, c;
	unsigned long val;

	if (!str) {
		return 0;
	}
	val = strtoul(str, &end, 0);
	if (!val || val == ULONG_MAX) {
		return 0;
	}
	while ((c = *end++) != 0) {
		switch (c) {
		case 'k':
			val <<= 10;
			break;
		case 'M':
			val <<= 20;
			break;
		case 'G':
			val <<= 30;
			break;
		default:
			return 0;
		}
	}
	return val;
}

void print_buf(const void *buf, size_t size, char *title)
{
	u32 i, j, p;

	if (title) {
		printf("%s\n", title);
	}

	if (size == 0) {
		printf("[%s][%d] SIZE is zero.\n\n", __FUNCTION__, __LINE__);
		return;
	}

	printf("0x%p: ", buf);

	for (i = 0; i < size; i++) {
		if (i && (i % 16 == 0)) {
			printf("   ");
			for (j = i - 16; j < i; j++) {
				if (((u8 *)buf)[j] < 0x20 || ((u8 *)buf)[j] > 0x7E) {
					printf(".");
				} else {
					printf("%c", ((char *)buf)[j]);
				}
			}
			printf("\n0x%p: ", buf);
			p = 1;
		} else if (i && (i % 8 == 0)) {
			printf(" ");
		}

		printf("%02X ", ((u8 *)buf)[i]);
		p = 0;
	}

	if (!p) {
		if (i % 16) {
			for (j = i; j < i + 16 - (i & 0xF); j++) {
				if (j % 8 == 0) {
					printf(" ");
				}

				printf("   ");
			}
		}

		printf("   ");

		for (j = i - ((i % 16) ? i % 16 : 16); j < i; j++) {
			if (((u8 *)buf)[j] < 0x20 || ((u8 *)buf)[j] > 0x7E) {
				printf(".");
			} else {
				printf("%c", ((char *)buf)[j]);
			}
		}
	}

	printf("\n\n");
}

/*
 *  strlen - Find the length of a string
 *  @s: The string to be sized
 */
size_t strlen(const char *s)
{
	const char *sc;
	for (sc = s; *sc != '\0'; ++sc)
		/* Do nothing*/;

	return sc - s;
}

#include "main.h"

#include "thread.h"
#include "nvme_mi.h"
#include "bin.h"
#include "crc_app.h"
#include "crc32.h"

#include "utility.h"

#include <time.h>
#include <stdint.h>

foo_ts foo = {.mutex = PTHREAD_MUTEX_INITIALIZER, .val = 0};

thread_info_t *m_thread_info0;
thread_info_t *m_thread_info1;
thread_info_t *m_thread_info2;
thread_info_t *m_thread_info3;

int thread_init(int argc, char *argv[])
{
	m_thread_info0 = malloc(sizeof(thread_info_t));
	m_thread_info0->thread_id = 0;
	m_thread_info0->sleep_nsec = THREAD_SLEEP_MSEC(500);
	pthread_create(&m_thread_info0->thread, NULL, main_thread0, m_thread_info0);

	m_thread_info1 = malloc(sizeof(thread_info_t));
	m_thread_info1->thread_id = 1;
	m_thread_info1->sleep_nsec = THREAD_SLEEP_MSEC(10);
	pthread_create(&m_thread_info1->thread, NULL, main_thread1, m_thread_info1);

	m_thread_info2 = malloc(sizeof(thread_info_t));
	m_thread_info2->thread_id = 2;
	m_thread_info2->sleep_nsec = THREAD_SLEEP_MSEC(300);
	pthread_create(&m_thread_info2->thread, NULL, main_thread2, m_thread_info2);

	m_thread_info3 = malloc(sizeof(thread_info_t));
	m_thread_info3->thread_id = 3;
	m_thread_info3->sleep_nsec = THREAD_SLEEP_MSEC(500);
	pthread_create(&m_thread_info3->thread, NULL, main_thread3, m_thread_info3);

	pthread_join(m_thread_info0->thread, NULL);
	pthread_join(m_thread_info1->thread, NULL);
	pthread_join(m_thread_info2->thread, NULL);
	pthread_join(m_thread_info3->thread, NULL);

	return 0;
}

int thread_delete(void)
{
	free(m_thread_info0);
	free(m_thread_info1);
	free(m_thread_info2);
	free(m_thread_info3);

	return 0;
}

int thread_test(int argc, char *argv[])
{
	printf("thread\n");
	srand(time(NULL));

	thread_init(argc, argv);
	thread_delete();

	return 0;
}

char msg[32];
char serial_num[20];

u8 name[] = {0x80};
char msg2[] = {0x80, 0x81, 0x01, 0x00, 0x00, 0x09};
char msg3[] = {0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x09};

// static u8 toupper(u8 c)
// {
//      if (c >= 'a' && c < 'z')
//      {
//              return c - 32;
//      }
//      else
//      {
//              return c;
//      }
// }

static void str2hex(void *h, const void *s, size_t len)
{
	char *hh = h;
	char const *ss = s;
	u8 c1, c2;

	len = len >> 1;

	while (len > 0) {
		// c1 = toupper(*ss++) - 'A';
		c1 = *ss++ - '0';
		if (c1 > 9)
			c1 = c1 - 7;

		// c2 = toupper(*ss++) - 'A';
		c2 = *ss++ - '0';
		if (c2 > 9)
			c2 = c2 - 7;

		*hh++ = (c1 << 4) + c2;
		len--;
	}
}

extern int crc_table_main(void);

union pause_cpsr_field {
	struct {
		word pfss0 : 1;
		word pfss1 : 1;
		word rsvd : 14;
	};
	word value;
};

#define likely(x)                       __builtin_expect(!!(x), 1)
#define unlikely(x)                     __builtin_expect(!!(x), 0)

void test1(void)
{
	volatile u32 count;
	clock_t start, end;

	count = UINT32_MAX >> 1;
	start = clock();
	while (1) {
		if (count == 0) {
			break;
		} else if (count % 10 == 0) {
			count--;
		} else {
			count--;
		}
	}
	end = clock();
	printf("time = (%ld,%ld,%lf)\n", start, end, (double)(end - start) / (double)CLOCKS_PER_SEC);
}

void test2(void)
{
	volatile u32 count;
	clock_t start, end;

	count = UINT32_MAX >> 1;
	start = clock();
	while (1) {
		if (unlikely(count == 0)) {
			break;
		} else if (count % 10 == 0) {
			count--;
		} else {
			count--;
		}
	}
	end = clock();
	printf("time = (%ld,%ld,%lf)\n", start, end, (double)(end - start) / (double)CLOCKS_PER_SEC);
}

void test3(void)
{
	volatile u32 count;
	clock_t start, end;

	count = UINT32_MAX >> 1;
	start = clock();
	while (1) {
		if (likely(count == 0)) {
			break;
		} else if (count % 10 == 0) {
			count--;
		} else {
			count--;
		}
	}
	end = clock();
	printf("time = (%ld,%ld,%lf)\n", start, end, (double)(end - start) / (double)CLOCKS_PER_SEC);
}

union u {
	struct {
		u32 b0 : 1;
		u32 b1 : 1;
		u32 b2 : 1;
		u32 b3 : 1;
		u32 b4 : 1;
		u32 b5 : 1;
		u32 b6 : 1;
		u32 b7 : 1;
		u32 b8 : 8;
		u32 b16 : 16;
		u32 b24: 8;
	};

	u32 value;
};

u32 test_compiler_optimize1(void)
{
	union u uu = {.value = rand()};
	return uu.b8;
}

u32 test_compiler_optimize2(void)
{
	u32 value;
#if 0
	value
	        = (1 << 31) | (1 << 30) | (1 << 29) | (1 << 28)
	          | (1 << 27) | (1 << 26) | (1 << 25) | (1 << 24)
	          | (1 << 23) | (1 << 22) | (1 << 21) | (1 << 20)
	          | (1 << 19) | (1 << 18) | (1 << 17) | (1 << 16)
	          | (1 << 15) | (1 << 14) | (1 << 13) | (1 << 12)
	          | (1 << 11) | (1 << 10) | (1 <<  9) | (1 <<  8)
	          | (1 <<  7) | (1 <<  6) | (1 <<  5) | (1 <<  4)
	          | (1 <<  3) | (1 <<  2) | (1 <<  1) | (1 <<  0);
#else
	value = rand();
#endif
	return (value >> 8) & 0xff;
}

int main(int argc, char *argv[])
{
#if 1
	int ret = 0;

	print_platform_info();

	printf("value = %x\n", test_compiler_optimize1());
	printf("value = %x\n", test_compiler_optimize2());

	//
	nvme_mi_test_checksum();

	//
	union pause_cpsr_field pause_cpsr;

	pause_cpsr.value = 0;
	printf("pfss0 = %d\n", pause_cpsr.pfss0);
	printf("pfss1 = %d\n", pause_cpsr.pfss1);

	pause_cpsr.pfss0 = (u8)1;
	pause_cpsr.pfss1 = !!0x80;
	printf("pfss0 = %d\n", pause_cpsr.pfss0);
	printf("pfss1 = %d\n", pause_cpsr.pfss1);

	crc_table_main();

	u32 crc;
	void *buf;
	int len;

	for (int i = 0; i < sizeof(serial_num); i++) {
		if (i < 12)
			serial_num[i] = ' ';
		else
			serial_num[i] = '0' + ((i + 1) % 10);
	}

	for (int i = 0; i < sizeof(serial_num); i++) {
		printf("%02x ", serial_num[i]);
	}
	printf("\n");

	u32 hex;
	str2hex(&hex, serial_num + 12, 8);
	printf("hex: 0x%08x\n", hex);

	smbus_calculate_pec();
	printf("\n");

	for (int i = 0; i < 30; i++) {
		msg[i] = i;
	}
	buf = msg;
	len = sizeof(msg) - 2;

	crc = ~crc32_halfbyte(CRC_INIT, buf, len);
	printf("crc-h:0x%08x\n", crc);

	crc = ~crc32_tableless3(CRC_INIT, buf, len, REVERSED_POLY);
	printf("crc-3:0x%08x\n", crc);

	crc = ~crc32_tableless2(CRC_INIT, buf, len, REVERSED_POLY);
	printf("crc-2:0x%08x\n", crc);

	crc = ~crc32_le_generic(CRC_INIT, buf, len, REVERSED_POLY);
	printf("crc-b:0x%08x\n", crc);

	crc = ~crc32(CRC_INIT, buf, len);
	printf("crc-0:0x%08x\n", crc);
	printf("\n");

	for (int i = 0; i < 32; i++) {
		msg[i] = 31 - i;
	}
	buf = msg;
	len = sizeof(msg);

	crc = ~crc32_halfbyte(CRC_INIT, buf, len);
	printf("crc-h:0x%08x\n", crc);

	crc = ~crc32_tableless3(CRC_INIT, buf, len, REVERSED_POLY);
	printf("crc-3:0x%08x\n", crc);

	crc = ~crc32_tableless2(CRC_INIT, buf, len, REVERSED_POLY);
	printf("crc-2:0x%08x\n", crc);

	crc = ~crc32_le_generic(CRC_INIT, buf, len, REVERSED_POLY);
	printf("crc-b:0x%08x\n", crc);

	crc = ~crc32(CRC_INIT, buf, len);
	printf("crc-0:0x%08x\n", crc);
	printf("\n");

	buf = msg2;
	len = sizeof(msg2);

	crc = ~crc32_halfbyte(CRC_INIT, buf, len);
	printf("crc-h:0x%08x\n", crc);

	crc = ~crc32_tableless3(CRC_INIT, buf, len, REVERSED_POLY);
	printf("crc-3:0x%08x\n", crc);

	crc = ~crc32_tableless2(CRC_INIT, buf, len, REVERSED_POLY);
	printf("crc-2:0x%08x\n", crc);

	crc = ~crc32_le_generic(CRC_INIT, buf, len, REVERSED_POLY);
	printf("crc-b:0x%08x\n", crc);

	crc = ~crc32(CRC_INIT, buf, len);
	printf("crc-0:0x%08x\n", crc);
	printf("\n");

	crc = ~crc32(crc, &crc, sizeof(crc));
	printf("final:0x%08x\n", crc);
	printf("\n");

	half_byte_table_generator();
#endif

	// test1();
	// test3();
	// test2();

	//
	ret = generate_random_binfile(argc, argv);
	if (ret) {
		printf("generate_random_binfile failed (%d)\n", ret);
	}

	// //
	// thread_test(argc, argv);

	buf = malloc(512);
	for (int i = 0; i < 512; i++) {
		*(u8 *)(buf + i) = 'a' + i;
	}
	print_buf(buf, 1, "");
	print_buf(buf, 8, "");
	print_buf(buf, 9, "");
	print_buf(buf, 16, "");
	print_buf(buf, 17, "");
	print_buf(buf, 32, "");
	print_buf(buf, 33, "");
	print_buf(buf, 256, "");
	print_buf(buf, 512, "");
	free(buf);

	return ret;
}

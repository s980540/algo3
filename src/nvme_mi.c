#include "global.h"
#include "nvme_mi.h"

#include "checksum.h"
#include "utility.h"

char string[] = {"The red fox jumps over a lazy dog."};

static void reverse(char *in, int len)
{
	char *c1 = in, *c2 = in + len - 1;

	while (1) {
		*c1 = *c1 ^ *c2;
		*c2 = *c1 ^ *c2;
		*c1 = *c1 ^ *c2;
		c1++;
		c2--;
		if (c1 >= c2) {
			break;
		}
	}
}

void nvme_mi_test_checksum(void)
{
	u8 sum, chksum;

	product_info_mname_t mname;

	sum = 0;
	sum = checksum8_append(sum, string, strlen(string));
	printf("sum: 0x%02x, %ld\n", sum, strlen(string));

	chksum = 0;
	chksum = checksum8(chksum, string, strlen(string));
	printf("checksum: 0x%02x, %ld\n", chksum, strlen(string));

	chksum += sum;
	printf("Checksum verify %s.\n", chksum ? "failed" : "passed");

	mname.ieee[0] = 'M';
	mname.ieee[1] = 'A';
	mname.ieee[2] = 'X';
	mname.ssvid = 0x0820;

	print_buf((char *)&mname, sizeof(mname), NULL);
	reverse((char *)&mname, sizeof(mname));
	print_buf((char *)&mname, sizeof(mname), NULL);
#ifdef AMD64
	printf("%llx %llx\n", (u64)&mname, (u64)mname.ieee);
#else
	printf("%x %x\n", (u32)&mname, (u32)mname.ieee);
#endif
}
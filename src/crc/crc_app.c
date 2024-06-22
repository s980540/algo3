#include "crc_app.h"

#include "crc8.h"

#define PATTERN_SEL (1)

#if (PATTERN_SEL == 1)
static const u8 i2c_data[] = {
	0x3a, 0x0f, 0x02, 0x12, 0x34
};
#elif (PATTERN_SEL == 2)
static const u8 i2c_data[] = {
	0x3a, 0x0f, 0x02, 0x56, 0x78
};
#elif (PATTERN_SEL == 3)
static const u8 i2c_data[] = {
	0x16, 0x0d, 0x17, 0x10, 0x00
};
#endif

void smbus_calculate_pec(void)
{
	u8 pec = crc8(0, i2c_data, sizeof(i2c_data));
	printf("pec:0x%02x\n", pec);
	pec = crc8_mr(0, i2c_data, sizeof(i2c_data));
	printf("pec (mr):0x%02x\n", pec);
	pec = crc8_linux(0, i2c_data, sizeof(i2c_data));
	printf("pec (linux):0x%02x\n", pec);
}

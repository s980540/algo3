#include "opt.h"

#define VERSION "1.0"

static void help(void) __attribute__((noreturn));

static void help(void)
{
	fprintf(stderr,
	        "Usage: i2cset [-f] [-y] [-m MASK] [-r] [-a] I2CBUS CHIP-ADDRESS DATA-ADDRESS [VALUE] ... [MODE]\n"
	        "  I2CBUS is an integer or an I2C bus name\n"
	        "  ADDRESS is an integer (0x08 - 0x77, or 0x00 - 0x7f if -a is given)\n"
	        "  MODE is one of:\n"
	        "    c (byte, no value)\n"
	        "    b (byte data, default)\n"
	        "    w (word data)\n"
	        "    i (I2C block data)\n"
	        "    s (SMBus block data)\n"
	        "    Append p for SMBus PEC\n");
	exit(1);
}

int opt_handle(int argc, char *argv[])
{
	int opt;
	int version = 0;

	while ((opt = getopt(argc, argv, "Vafhm:ry")) != -1) {
		switch (opt) {
		case 'v':
			version = 1;
			break;
		case 'h':
			help();
			break;
		}
	}

	if (version) {
		fprintf(stderr, "aardvark version %s\n", VERSION);
		exit(0);
	}

	return 0;
}

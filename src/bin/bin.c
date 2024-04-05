#include "bin.h"

#include "global.h"
#include "utility.h"

int generate_random_binfile(int argc, char *argv[])
{
    char *file_name;
    u32 bin_size;
    FILE *fp = NULL;
    int ret = 0;

    if (argc < 2) {
        printf("bad arguments: algo <file name> <bin size(k/M/G)>\n");
        return -1;
    }

    srand(time(NULL));

    file_name = argv[1];
    bin_size = get_num(argv[2]);

    if (bin_size == 0) {
        printf("bad arguments: algo <file name> <bin size(k/M/G)>\n");
        return -1;
    }

    printf("%s\n", __FUNCTION__);
    printf("File Name: %s\n", file_name);
    printf("Bin Size: %d\n", bin_size);

    #if (OPT_BIN_DEBUG)
    char *bin = malloc(bin_size);
    u32 i = 0;
    #endif

    fp = fopen(file_name, "wb");
    if (fp == NULL) {
        printf("fopen failed\n");
        goto exit;
    }

    while (bin_size-- > 0) {
        char c = rand() & 0xFF;
        #if (OPT_BIN_DEBUG)
        bin[i++] = c;
        #endif
        ret = fputc(c, fp);
        if (ret == EOF) {
            ret = ferror(fp);
            printf("fputc failed (%d)\n", ret);
            perror("fputc failed");
            clearerr(fp);
            goto exit;
        }
    }

exit:
    ret = fclose(fp);
    #if (OPT_BIN_DEBUG)
    printf("fclose (%d)\n", ret);
    #endif
    if (ret == EOF) {
        ret = ferror(fp);
        printf("fclose failed (%d)\n", ret);
        perror("fclose failed");
        clearerr(fp);
    }

    #if (OPT_BIN_DEBUG)
    print_buf(bin, i, file_name);
    #endif

    return ret;
}
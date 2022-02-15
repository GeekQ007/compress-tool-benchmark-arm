#include "compress_api.h"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("error argc < 2");
    }
    remove("out.llz4hc");
    lz4hc_compress_pack("out.llz4hc", argv[1], argv[2], argv[3], argv[4], argv[5]);
    return 0;
}
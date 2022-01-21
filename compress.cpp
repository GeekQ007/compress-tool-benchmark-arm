#include "compress_api.h"

int main(int argc, char **argv)
{
    cmdline::parser args;
    args.add<std::string>("src", 's', "origin file", true);
    args.add<std::string>("dst", 'd', "compressed file", true);
    args.add<int>("level", 'l', "compresse level", false);
    args.add<int>("type", 't', "compressed tool type:\n\
                                        \t 0: zlib\n\
                                        \t 1: lz4\n\
                                        \t 2: lz4hc\n\
                                        \t 3: snappy",
                  false, 0); /* Note: if new tool supported, change here too. */
    args.parse_check(argc, argv);
    int ret = 0;
    const char *origin_file = args.get<std::string>("src").c_str();
    const char *compressed_file = args.get<std::string>("dst").c_str();
    COMPRESS_META compress_meta;
    compress_meta.level = args.get<int>("level");
    compress_meta.type = (COMPRESS_TYPE)args.get<int>("type");

    FILE *src = fopen(origin_file, "r");
    FILE *dst = fopen(compressed_file, "w");
    ret = compress(src, dst, compress_meta);
    if (ret)
    {
        printf("compress failed \n");
        return -1;
    }
    fclose(src);
    fclose(dst);
    return 0;
}
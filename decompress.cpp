#include "compress_api.h"

int main(int argc, char **argv)
{
    cmdline::parser args;

    args.add<std::string>("src", 's', "compressed file", true);
    args.add<int>("type", 't', "decompressed tool type:\n\
                                        \t 0: zlib\n\
                                        \t 1: lz4\n\
                                        \t 2: lz4hc\n\
                                        \t 3: snappy",
                  false, 0); /* Note: if new tool supported, change here too. */
    args.parse_check(argc, argv);
    int ret = 0;
    const char *compressed_file = args.get<std::string>("src").c_str();
    struct timeval start, end;
    COMPRESS_META compress_meta;
    memset(&compress_meta, 0, sizeof(compress_meta));

    compress_meta.type = (COMPRESS_TYPE)args.get<int>("type");
    compress_meta.buffer_size = 512 * 512;

    std::vector<char> compressed;
    if (!read_file(compressed_file, compressed))
    {
        printf("read file failed\n");
        return -1;
    }

    std::vector<char> dpressed(200 * 1024 * 1024);
    gettimeofday(&start, NULL);
    ret = decompress(compressed, dpressed, compress_meta);
    if (ret)
    {
        printf("error decompress! \n");
        return 0;
    }
    gettimeofday(&end, NULL);
    printf("time cost %lf ms \n", ((end.tv_sec * 1000.0 + end.tv_usec / 1000.0) - (start.tv_sec * 1000.0 + start.tv_usec / 1000.0)));

    return 0;
}
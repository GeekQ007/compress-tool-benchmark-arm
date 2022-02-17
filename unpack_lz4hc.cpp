#include "compress_api.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("error argc != 2");
    }
    FILE *src = fopen(argv[1], "rb");
    std::vector<char> data;
    read_file(src, data);
    part_info *header = (part_info *)data.data();
    printf("part num: %d part0 name %s offset %d cmp size %d decmp_size %d \n", header[0].cmp_size, header[1].name, header[1].offset, header[1].cmp_size, header[1].decmp_size);
    fclose(src);
    return 0;
}
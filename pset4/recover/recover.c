#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint8_t isZero(uint8_t array[512])
{
    for (uint16_t i = 0; i < 512; i++)
    {
        if (array[i] != 0)
        {
            return 0;
        }
    }

    return 1;
}

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        return 1;
    }

    uint8_t buffer[512];
    char fileName[8];
    uint8_t jpegCounter = 0;

    FILE *file = fopen(argv[1], "r");

    if (NULL == file)
    {
        return 1;
    }

    while (!feof(file))
    {
        if (fread(buffer, sizeof(uint8_t), 512, file) != 512)
        {
            break;
        }

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            sprintf(fileName, "%03d.jpg", jpegCounter);
            jpegCounter++;
        }

        if (jpegCounter > 0 && !isZero(buffer))
        {
            FILE *out = fopen(fileName, "a");

            fwrite(buffer, sizeof(uint8_t), 512, out);

            fclose(out);
        }
    }

    fclose(file);

    return 0;
}

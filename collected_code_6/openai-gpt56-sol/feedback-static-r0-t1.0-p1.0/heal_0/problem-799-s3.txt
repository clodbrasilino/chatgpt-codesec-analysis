#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t rotate_left(uint32_t value, unsigned int count)
{
    const unsigned int width = (unsigned int)(sizeof(value) * CHAR_BIT);

    count %= width;
    return count == 0U
        ? value
        : (uint32_t)((value << count) | (value >> (width - count)));
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long value;
    unsigned long count;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <uint32> <rotation>\n", argv[0]);
        return EXIT_FAILURE;
    }

    value = strtoul(argv[1], &end, 0);
    if (end == argv[1] || *end != '\0' || value > UINT32_MAX) {
        fprintf(stderr, "Invalid uint32 value\n");
        return EXIT_FAILURE;
    }

    end = NULL;
    count = strtoul(argv[2], &end, 0);
    if (end == argv[2] || *end != '\0') {
        fprintf(stderr, "Invalid rotation count\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu32 "\n", rotate_left((uint32_t)value, (unsigned int)(count % 32UL)));
    return EXIT_SUCCESS;
}
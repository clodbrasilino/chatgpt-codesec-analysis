#include <errno.h>
#include <inttypes.h>
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
    char *end;
    uintmax_t value;
    uintmax_t count;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <uint32> <rotation>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    value = strtoumax(argv[1], &end, 0);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || value > UINT32_MAX) {
        fprintf(stderr, "Invalid uint32 value\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    count = strtoumax(argv[2], &end, 0);

    if (errno == ERANGE || end == argv[2] || *end != '\0' ||
        argv[2][0] == '-') {
        fprintf(stderr, "Invalid rotation count\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu32 "\n",
           rotate_left((uint32_t)value, (unsigned int)(count % 32U)));

    return EXIT_SUCCESS;
}
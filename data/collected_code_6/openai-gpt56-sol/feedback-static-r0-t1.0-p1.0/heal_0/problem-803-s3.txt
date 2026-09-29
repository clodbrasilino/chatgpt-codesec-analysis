#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_perfect_square(uint64_t number)
{
    uint64_t low = 0;
    uint64_t high = number < UINT64_C(4294967295)
                        ? number
                        : UINT64_C(4294967295);

    while (low <= high) {
        uint64_t middle = low + (high - low) / 2;

        if (middle != 0 && middle > number / middle) {
            high = middle - 1;
        } else {
            uint64_t square = middle * middle;

            if (square == number) {
                return 1;
            }

            low = middle + 1;
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t value;

    if (argc != 2) {
        (void)fprintf(stderr, "Usage: %s <non-negative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || value > UINT64_MAX) {
        (void)fprintf(stderr, "Invalid non-negative integer.\n");
        return EXIT_FAILURE;
    }

    (void)printf("%" PRIuMAX " is %sa perfect square.\n",
                 value, is_perfect_square((uint64_t)value) ? "" : "not ");

    return EXIT_SUCCESS;
}
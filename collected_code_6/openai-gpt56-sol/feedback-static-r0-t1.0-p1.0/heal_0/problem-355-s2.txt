#include <errno.h>
#include <inttypes.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_rectangles(uint64_t radius, uint64_t *count)
{
    uint64_t total = 0;

    if (count == NULL || radius > (uint64_t)INT64_MAX) {
        return 0;
    }

    for (uint64_t width = 1; width <= radius; ++width) {
        const long double r = (long double)radius;
        const long double w = (long double)width;
        const long double remaining = r * r - w * w;
        const uint64_t max_height =
            remaining > 0.0L ? (uint64_t)sqrtl(remaining) : 0;

        if (UINT64_MAX - total < max_height) {
            return 0;
        }

        total += max_height;
    }

    *count = total;
    return 1;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s radius\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoumax(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || input > UINT64_MAX) {
        fputs("Invalid radius\n", stderr);
        return EXIT_FAILURE;
    }

    if (!count_rectangles((uint64_t)input, &result)) {
        fputs("Unable to count rectangles\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}
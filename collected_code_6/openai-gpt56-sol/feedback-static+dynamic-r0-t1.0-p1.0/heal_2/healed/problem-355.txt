#include <errno.h>
#include <inttypes.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_rectangles(uint64_t radius, uint64_t *result)
{
    uint64_t count = 0;
    uint64_t width_limit;
    uint64_t r_squared;

    if (result == NULL || radius == 0 ||
        radius > UINT64_C(3037000499)) {
        return -1;
    }

    r_squared = radius * radius;
    width_limit = (uint64_t)(sqrtl(2.0L * (long double)r_squared) + 1.0L);

    for (uint64_t width = 1; width <= width_limit; ++width) {
        const uint64_t width_squared = width * width;
        const uint64_t limit = 4 * r_squared - width_squared;
        uint64_t low = 1;
        uint64_t high = width;
        uint64_t max_height = 0;

        while (low <= high) {
            const uint64_t mid = low + (high - low) / 2;
            const uint64_t mid_squared = mid * mid;

            if (mid_squared <= limit) {
                max_height = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        if (UINT64_MAX - count < max_height) {
            return -1;
        }

        count += max_height;
    }

    *result = count;
    return 0;
}

int main(int argc, char *const argv[])
{
    char *end = NULL;
    uintmax_t parsed_radius;
    uint64_t rectangle_count;

    if (argc != 2) {
        const char *program = argc > 0 && argv[0] != NULL ? argv[0] : "program";
        fprintf(stderr, "Usage: %s <positive integer radius>\n", program);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_radius = strtoumax(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' ||
        parsed_radius == 0 ||
        parsed_radius > UINT64_C(3037000499)) {
        fputs("Invalid radius\n", stderr);
        return EXIT_FAILURE;
    }

    if (count_rectangles((uint64_t)parsed_radius, &rectangle_count) != 0) {
        fputs("Unable to count rectangles\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", rectangle_count);
    return EXIT_SUCCESS;
}
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned long long count_rectangles(unsigned int radius)
{
    unsigned long long count = 0;
    const unsigned long long diameter_squared =
        4ULL * (unsigned long long)radius * radius;

    for (unsigned int width = 1; width <= 2U * radius; ++width) {
        for (unsigned int height = 1; height <= width; ++height) {
            const unsigned long long diagonal_squared =
                (unsigned long long)width * width +
                (unsigned long long)height * height;

            if (diagonal_squared <= diameter_squared) {
                count += (width == height) ? 1ULL : 2ULL;
            }
        }
    }

    return count;
}

int main(int argc, const char *const argv[])
{
    char *end = NULL;
    unsigned long input;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <radius>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoul(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' ||
        input == 0 || input > UINT_MAX / 2U) {
        fprintf(stderr, "Invalid radius\n");
        return EXIT_FAILURE;
    }

    printf("%llu\n", count_rectangles((unsigned int)input));
    return EXIT_SUCCESS;
}
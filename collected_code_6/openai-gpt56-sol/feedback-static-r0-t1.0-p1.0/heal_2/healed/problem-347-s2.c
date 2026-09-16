#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_squares(uint64_t width, uint64_t height, uint64_t *result)
{
    uint64_t sum = 0;
    const uint64_t limit = width < height ? width : height;

    if (result == NULL) {
        return 0;
    }

    for (uint64_t side = 1; side <= limit; ++side) {
        const uint64_t horizontal = width - side + 1;
        const uint64_t vertical = height - side + 1;

        if (vertical > UINT64_MAX / horizontal) {
            return 0;
        }

        const uint64_t count = horizontal * vertical;

        if (sum > UINT64_MAX - count) {
            return 0;
        }

        sum += count;
    }

    *result = sum;
    return 1;
}

static int parse_dimension(const char *text, uint64_t *value)
{
    char *end = NULL;
    uintmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

int main(int argc, const char *argv[])
{
    uint64_t width;
    uint64_t height;
    uint64_t result;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <width> <height>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_dimension(argv[1], &width) ||
        !parse_dimension(argv[2], &height)) {
        fprintf(stderr, "Dimensions must be non-negative integers.\n");
        return EXIT_FAILURE;
    }

    if (!count_squares(width, height, &result)) {
        fprintf(stderr, "Square count exceeds the supported range.\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int count_squares(uint64_t width, uint64_t height, uint64_t *result)
{
    const uint64_t smaller = width < height ? width : height;
    const uint64_t larger = width < height ? height : width;
    const __uint128_t n = smaller;
    const __uint128_t m = larger;
    const __uint128_t count =
        n * (n + 1U) * (3U * m - n + 1U) / 6U;

    if (result == NULL || count > UINT64_MAX) {
        return -1;
    }

    *result = (uint64_t)count;
    return 0;
}

static int parse_dimension(const char *text, uint64_t *value)
{
    char *end = NULL;
    uintmax_t parsed;

    if (text == NULL || value == NULL || text[0] == '\0' ||
        text[0] == '-') {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > UINT64_MAX) {
        return -1;
    }

    *value = (uint64_t)parsed;
    return 0;
}

int main(int argc, const char *const argv[])
{
    uint64_t width;
    uint64_t height;
    uint64_t result;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <width> <height>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (parse_dimension(argv[1], &width) != 0 ||
        parse_dimension(argv[2], &height) != 0) {
        fprintf(stderr, "Invalid dimensions\n");
        return EXIT_FAILURE;
    }

    if (count_squares(width, height, &result) != 0) {
        fprintf(stderr, "Result exceeds the supported range\n");
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
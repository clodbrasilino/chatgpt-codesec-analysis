#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t minimum_operations(int64_t first, int64_t second)
{
    uint64_t magnitude_first = first < 0
        ? (uint64_t)(-(first + 1)) + UINT64_C(1)
        : (uint64_t)first;
    uint64_t magnitude_second = second < 0
        ? (uint64_t)(-(second + 1)) + UINT64_C(1)
        : (uint64_t)second;

    if ((first < 0) != (second < 0)) {
        return magnitude_first + magnitude_second;
    }

    return magnitude_first >= magnitude_second
        ? magnitude_first - magnitude_second
        : magnitude_second - magnitude_first;
}

static int parse_int64(const char *text, int64_t *value)
{
    char *end = NULL;
    intmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0') {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

int main(int argc, char *argv[])
{
    int64_t first;
    int64_t second;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <first> <second>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_int64(argv[1], &first) || !parse_int64(argv[2], &second)) {
        fprintf(stderr, "Invalid integer input\n");
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", minimum_operations(first, second)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
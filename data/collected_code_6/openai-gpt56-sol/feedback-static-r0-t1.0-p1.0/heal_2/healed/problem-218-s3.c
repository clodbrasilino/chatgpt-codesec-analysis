#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t minimum_operations(int64_t first, int64_t second)
{
    const uint64_t a = (uint64_t)first;
    const uint64_t b = (uint64_t)second;

    return first >= second ? a - b : b - a;
}

static int parse_int64(const char *text, int64_t *value)
{
    char *end = NULL;
    intmax_t parsed;

    errno = 0;
    parsed = strtoimax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

int main(int argc, const char *const argv[])
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
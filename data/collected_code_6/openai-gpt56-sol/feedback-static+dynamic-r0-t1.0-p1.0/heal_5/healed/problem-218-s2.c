#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t magnitude_int64(int64_t value)
{
    return value < 0
        ? (uint64_t)(-(value + INT64_C(1))) + UINT64_C(1)
        : (uint64_t)value;
}

static uint64_t minimum_operations(int64_t first, int64_t second)
{
    uint64_t first_magnitude = magnitude_int64(first);
    uint64_t second_magnitude = magnitude_int64(second);
    uint64_t difference = first_magnitude >= second_magnitude
        ? first_magnitude - second_magnitude
        : second_magnitude - first_magnitude;
    uint64_t operations =
        difference / UINT64_C(2) + difference % UINT64_C(2);

    if (first != second && (first < 0) != (second < 0)) {
        operations += UINT64_C(4);
    }

    return operations;
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

int main(int argc, char *const argv[])
{
    int64_t first;
    int64_t second;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <first> <second>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_int64(argv[1], &first) ||
        !parse_int64(argv[2], &second)) {
        fputs("Invalid integer input\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n",
               minimum_operations(first, second)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_hexadecimal_numbers(uint64_t lower, uint64_t upper,
                                     uint64_t *count)
{
    if (count == NULL || lower > upper ||
        (lower == 0 && upper == UINT64_MAX)) {
        return -1;
    }

    *count = upper - lower + UINT64_C(1);
    return 0;
}

static int parse_uint64(const char *text, uint64_t *value)
{
    char *end = NULL;
    uintmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 0);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > UINT64_MAX) {
        return -1;
    }

    *value = (uint64_t)parsed;
    return 0;
}

int main(int argc, const char *const argv[])
{
    uint64_t lower;
    uint64_t upper;
    uint64_t count;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <lower> <upper>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (parse_uint64(argv[1], &lower) != 0 ||
        parse_uint64(argv[2], &upper) != 0) {
        fputs("Invalid range value\n", stderr);
        return EXIT_FAILURE;
    }

    if (count_hexadecimal_numbers(lower, upper, &count) != 0) {
        fputs("Invalid or unrepresentable range\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", count);
    return EXIT_SUCCESS;
}
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t integer_sqrt(uint64_t value)
{
    uint64_t low = 0;
    uint64_t high = value < UINT32_MAX ? value : UINT32_MAX;
    uint64_t result = 0;

    while (low <= high) {
        const uint64_t mid = low + (high - low) / 2;

        if (mid == 0 || mid <= value / mid) {
            result = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return result;
}

static int print_perfect_squares(uint64_t lower, uint64_t upper)
{
    uint64_t root;

    if (lower > upper) {
        return -1;
    }

    root = integer_sqrt(lower);
    if (root * root < lower) {
        ++root;
    }

    while (root <= UINT32_MAX && root <= upper / root) {
        const uint64_t square = root * root;

        if (printf("%" PRIu64 "\n", square) < 0) {
            return -1;
        }

        ++root;
    }

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
    uint64_t lower;
    uint64_t upper;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <lower> <upper>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (parse_uint64(argv[1], &lower) != 0 ||
        parse_uint64(argv[2], &upper) != 0) {
        fputs("Both bounds must be non-negative integers.\n", stderr);
        return EXIT_FAILURE;
    }

    if (lower > upper) {
        fputs("The lower bound must not exceed the upper bound.\n", stderr);
        return EXIT_FAILURE;
    }

    if (print_perfect_squares(lower, upper) != 0) {
        fputs("Failed to print perfect squares.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
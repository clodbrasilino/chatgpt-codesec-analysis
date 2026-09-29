#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t integer_sqrt(uint64_t value)
{
    uint64_t low = 0;
    uint64_t high = value < UINT64_C(0xFFFFFFFF) ? value : UINT64_C(0xFFFFFFFF);
    uint64_t result = 0;

    while (low <= high) {
        uint64_t middle = low + (high - low) / 2;

        if (middle == 0 || middle <= value / middle) {
            result = middle;
            low = middle + 1;
        } else {
            high = middle - 1;
        }
    }

    return result;
}

static int find_perfect_squares(uint64_t lower, uint64_t upper)
{
    uint64_t root;
    uint64_t first_root;
    int found = 0;

    if (lower > upper) {
        return -1;
    }

    root = integer_sqrt(lower);
    first_root = root;

    if (root * root < lower) {
        ++first_root;
    }

    root = integer_sqrt(upper);

    if (first_root > root) {
        printf("No perfect squares found.\n");
        return 0;
    }

    for (uint64_t current = first_root; current <= root; ++current) {
        printf("%" PRIu64 "\n", current * current);
        found = 1;

        if (current == root) {
            break;
        }
    }

    return found;
}

static int parse_uint64(const char *text, uint64_t *value)
{
    char *end = NULL;
    uintmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' || parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

int main(int argc, char *argv[])
{
    uint64_t lower;
    uint64_t upper;
    int result;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <lower> <upper>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_uint64(argv[1], &lower) || !parse_uint64(argv[2], &upper)) {
        fprintf(stderr, "Both bounds must be valid non-negative integers.\n");
        return EXIT_FAILURE;
    }

    result = find_perfect_squares(lower, upper);

    if (result < 0) {
        fprintf(stderr, "The lower bound must not exceed the upper bound.\n");
        return EXIT_FAILURE;
    }

    if (ferror(stdout)) {
        fprintf(stderr, "Failed to write output.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
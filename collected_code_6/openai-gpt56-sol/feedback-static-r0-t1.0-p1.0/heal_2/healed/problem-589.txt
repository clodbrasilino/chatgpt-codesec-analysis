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
        const uint64_t middle = low + (high - low) / 2;

        if (middle == 0 || middle <= value / middle) {
            result = middle;
            low = middle + 1;
        } else {
            high = middle - 1;
        }
    }

    return result;
}

static void print_perfect_squares(uint64_t lower, uint64_t upper)
{
    if (lower > upper) {
        const uint64_t temporary = lower;
        lower = upper;
        upper = temporary;
    }

    uint64_t root = integer_sqrt(lower);

    if (root * root < lower) {
        ++root;
    }

    while (root != 0 && root <= upper / root) {
        printf("%" PRIu64 "\n", root * root);
        ++root;
    }
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

int main(int argc, const char *const argv[])
{
    uint64_t lower;
    uint64_t upper;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <lower> <upper>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_uint64(argv[1], &lower) || !parse_uint64(argv[2], &upper)) {
        fprintf(stderr, "Both bounds must be non-negative integers.\n");
        return EXIT_FAILURE;
    }

    print_perfect_squares(lower, upper);

    return EXIT_SUCCESS;
}
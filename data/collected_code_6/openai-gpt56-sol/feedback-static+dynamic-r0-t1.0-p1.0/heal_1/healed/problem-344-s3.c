#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include <errno.h>

static uint64_t integer_sqrt(uint64_t value)
{
    uint64_t low = 0;
    uint64_t high = value < UINT64_C(4294967295)
                        ? value
                        : UINT64_C(4294967295);
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

static uint64_t count_elements_with_odd_number_of_factors(uint64_t lower,
                                                           uint64_t upper)
{
    uint64_t first_root;
    uint64_t last_root;

    if (lower > upper) {
        return 0;
    }

    first_root = integer_sqrt(lower);
    if (first_root * first_root < lower) {
        ++first_root;
    }

    last_root = integer_sqrt(upper);

    return first_root > last_root ? 0 : last_root - first_root + 1;
}

static int parse_uint64(const char **input, uint64_t *value)
{
    const char *cursor = *input;
    char *end;
    uintmax_t parsed;

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '\0' || *cursor == '+' || *cursor == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(cursor, &end, 10);

    if (cursor == end || errno == ERANGE || parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    *input = end;
    return 1;
}

int main(void)
{
    char input[256];
    const char *cursor;
    uint64_t lower;
    uint64_t upper;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    cursor = input;

    if (!parse_uint64(&cursor, &lower) || !parse_uint64(&cursor, &upper)) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (lower > upper) {
        fprintf(stderr, "Invalid range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n",
           count_elements_with_odd_number_of_factors(lower, upper));

    return EXIT_SUCCESS;
}
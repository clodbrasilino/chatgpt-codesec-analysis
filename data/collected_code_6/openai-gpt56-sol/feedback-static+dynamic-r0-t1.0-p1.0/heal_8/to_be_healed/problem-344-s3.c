#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>

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

static int discard_line(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    return ch == '\n' || !ferror(stdin);
}

static int read_input_line(char *buffer, size_t size)
{
    size_t length;

    if (buffer == NULL || size < 2) {
        return 0;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return 0;
    }

    for (length = 0; length < size && buffer[length] != '\0'; ++length) {
        if (buffer[length] == '\n') {
            return 1;
        }
    }

    if (length == size || length == 0) {
        return 0;
    }

    if (feof(stdin)) {
        return 1;
    }

    discard_line();
    return 0;
}

static int parse_uint64(const char **cursor, uint64_t *value)
{
    const unsigned char *p;
    uint64_t result = 0;

    if (cursor == NULL || *cursor == NULL || value == NULL) {
        return 0;
    }

    p = (const unsigned char *)*cursor;

    while (*p != '\0' && isspace(*p)) {
        ++p;
    }

    if (!isdigit(*p)) {
        return 0;
    }

    do {
        unsigned int digit = (unsigned int)(*p - (unsigned char)'0');

        if (result > (UINT64_MAX - digit) / UINT64_C(10)) {
            return 0;
        }

        result = result * UINT64_C(10) + digit;
        ++p;
    } while (isdigit(*p));

    if (*p != '\0' && !isspace(*p)) {
        return 0;
    }

    *cursor = (const char *)p;
    *value = result;
    return 1;
}

static int parse_input(const char *input, uint64_t *lower, uint64_t *upper)
{
    const char *cursor = input;

    if (!parse_uint64(&cursor, lower) || !parse_uint64(&cursor, upper)) {
        return 0;
    }

    while (*cursor != '\0' && isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    return *cursor == '\0';
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    uint64_t lower;
    uint64_t upper;

    if (!read_input_line(input, sizeof input) ||
        !parse_input(input, &lower, &upper)) {
        if (ferror(stdin)) {
            fputs("Input error\n", stderr);
        } else {
            fputs("Invalid input\n", stderr);
        }
        return EXIT_FAILURE;
    }

    if (lower > upper) {
        fputs("Invalid range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n",
               count_elements_with_odd_number_of_factors(lower, upper)) < 0) {
        fputs("Output error\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
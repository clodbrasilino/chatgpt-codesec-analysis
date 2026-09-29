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

    if (first_root < UINT64_C(4294967295) &&
        first_root * first_root < lower) {
        ++first_root;
    }

    last_root = integer_sqrt(upper);

    return first_root > last_root ? 0 : last_root - first_root + 1;
}

static int read_uint64(uint64_t *value)
{
    int ch;
    uint64_t result = 0;

    if (value == NULL) {
        return 0;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return 0;
    }

    if (!isdigit((unsigned char)ch)) {
        return 0;
    }

    do {
        unsigned int digit = (unsigned int)(ch - '0');

        if (result > (UINT64_MAX - digit) / UINT64_C(10)) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = fgetc(stdin);
            } while (ch != EOF && isdigit((unsigned char)ch));
            return 0;
        }

        result = result * UINT64_C(10) + digit;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != EOF && isdigit((unsigned char)ch));

    if (ch != EOF && !isspace((unsigned char)ch)) {
        return 0;
    }

    if (ch != EOF && ungetc(ch, stdin) == EOF) {
        return 0;
    }

    *value = result;
    return 1;
}

static int only_whitespace_remains(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF) {
        if (!isspace((unsigned char)ch)) {
            return 0;
        }
    }

    return !ferror(stdin);
}

int main(void)
{
    uint64_t lower;
    uint64_t upper;

    errno = 0;

    if (!read_uint64(&lower) ||
        !read_uint64(&upper) ||
        !only_whitespace_remains()) {
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
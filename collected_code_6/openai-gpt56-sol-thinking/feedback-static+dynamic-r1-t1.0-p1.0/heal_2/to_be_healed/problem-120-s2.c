#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int32_t first;
    int32_t second;
} Tuple;

static int next_non_whitespace(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != EOF && isspace((unsigned char)ch));

    return ch;
}

static bool valid_token_end(int ch)
{
    if (ch == EOF) {
        return !ferror(stdin);
    }

    return isspace((unsigned char)ch) != 0;
}

static bool read_size_value(size_t *value)
{
    if (value == NULL) {
        return false;
    }

    int ch = next_non_whitespace();
    if (ch == EOF) {
        return false;
    }

    if (ch == '+') {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } else if (ch == '-') {
        return false;
    }

    if (ch < '0' || ch > '9') {
        return false;
    }

    size_t parsed = 0;
    bool overflow = false;

    do {
        size_t digit = (size_t)(ch - '0');

        if (!overflow) {
            if (parsed > (SIZE_MAX - digit) / 10) {
                overflow = true;
            } else {
                parsed = parsed * 10 + digit;
            }
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch >= '0' && ch <= '9');

    if (overflow || !valid_token_end(ch)) {
        return false;
    }

    *value = parsed;
    return true;
}

static bool read_int32_value(int32_t *value)
{
    if (value == NULL) {
        return false;
    }

    int ch = next_non_whitespace();
    if (ch == EOF) {
        return false;
    }

    bool negative = false;

    if (ch == '+' || ch == '-') {
        negative = ch == '-';
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    if (ch < '0' || ch > '9') {
        return false;
    }

    const uint64_t limit = negative
        ? (uint64_t)INT32_MAX + 1
        : (uint64_t)INT32_MAX;

    uint64_t magnitude = 0;
    bool overflow = false;

    do {
        uint64_t digit = (uint64_t)(ch - '0');

        if (!overflow) {
            if (magnitude > (limit - digit) / 10) {
                overflow = true;
            } else {
                magnitude = magnitude * 10 + digit;
            }
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch >= '0' && ch <= '9');

    if (overflow || !valid_token_end(ch)) {
        return false;
    }

    if (negative) {
        *value = magnitude == (uint64_t)INT32_MAX + 1
            ? INT32_MIN
            : -(int32_t)magnitude;
    } else {
        *value = (int32_t)magnitude;
    }

    return true;
}

static bool find_maximum_product(const Tuple *tuples, size_t count,
                                 int64_t *result)
{
    if (tuples == NULL || result == NULL || count == 0) {
        return false;
    }

    int64_t maximum =
        (int64_t)tuples[0].first * (int64_t)tuples[0].second;

    for (size_t i = 1; i < count; ++i) {
        int64_t product =
            (int64_t)tuples[i].first * (int64_t)tuples[i].second;

        if (product > maximum) {
            maximum = product;
        }
    }

    *result = maximum;
    return true;
}

int main(void)
{
    size_t count;

    if (!read_size_value(&count) ||
        count == 0 ||
        count > SIZE_MAX / sizeof(Tuple)) {
        return EXIT_FAILURE;
    }

    Tuple *tuples = malloc(count * sizeof(*tuples));
    if (tuples == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_int32_value(&tuples[i].first) ||
            !read_int32_value(&tuples[i].second)) {
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    int64_t maximum;

    if (!find_maximum_product(tuples, count, &maximum)) {
        free(tuples);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", maximum) < 0) {
        free(tuples);
        return EXIT_FAILURE;
    }

    free(tuples);
    return EXIT_SUCCESS;
}
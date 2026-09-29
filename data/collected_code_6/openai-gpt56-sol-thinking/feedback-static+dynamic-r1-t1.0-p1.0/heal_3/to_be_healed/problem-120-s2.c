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

typedef struct {
    FILE *stream;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[4096];
    size_t position;
    size_t length;
    bool failed;
} InputScanner;

static void scanner_init(InputScanner *scanner, FILE *stream)
{
    scanner->stream = stream;
    scanner->position = 0;
    scanner->length = 0;
    scanner->failed = false;
}

static int scanner_get(InputScanner *scanner)
{
    if (scanner == NULL || scanner->stream == NULL || scanner->failed) {
        return EOF;
    }

    if (scanner->position == scanner->length) {
        scanner->length = fread(scanner->buffer, 1,
                                sizeof(scanner->buffer), scanner->stream);
        scanner->position = 0;

        if (scanner->length == 0) {
            if (ferror(scanner->stream)) {
                scanner->failed = true;
            }
            return EOF;
        }
    }

    return scanner->buffer[scanner->position++];
}

static int next_non_whitespace(InputScanner *scanner)
{
    int ch;

    do {
        ch = scanner_get(scanner);
    } while (ch != EOF && isspace((unsigned char)ch));

    return ch;
}

static bool valid_token_end(const InputScanner *scanner, int ch)
{
    if (ch == EOF) {
        return scanner != NULL && !scanner->failed;
    }

    return isspace((unsigned char)ch) != 0;
}

static bool read_size_value(InputScanner *scanner, size_t *value)
{
    if (scanner == NULL || value == NULL) {
        return false;
    }

    int ch = next_non_whitespace(scanner);

    if (ch == EOF) {
        return false;
    }

    if (ch == '+') {
        ch = scanner_get(scanner);
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

        ch = scanner_get(scanner);
    } while (ch >= '0' && ch <= '9');

    if (overflow || !valid_token_end(scanner, ch)) {
        return false;
    }

    *value = parsed;
    return true;
}

static bool read_int32_value(InputScanner *scanner, int32_t *value)
{
    if (scanner == NULL || value == NULL) {
        return false;
    }

    int ch = next_non_whitespace(scanner);

    if (ch == EOF) {
        return false;
    }

    bool negative = false;

    if (ch == '+' || ch == '-') {
        negative = ch == '-';
        ch = scanner_get(scanner);
    }

    if (ch < '0' || ch > '9') {
        return false;
    }

    const uint64_t limit = negative
        ? (uint64_t)INT32_MAX + UINT64_C(1)
        : (uint64_t)INT32_MAX;

    uint64_t magnitude = 0;
    bool overflow = false;

    do {
        uint64_t digit = (uint64_t)(ch - '0');

        if (!overflow) {
            if (magnitude > (limit - digit) / UINT64_C(10)) {
                overflow = true;
            } else {
                magnitude = magnitude * UINT64_C(10) + digit;
            }
        }

        ch = scanner_get(scanner);
    } while (ch >= '0' && ch <= '9');

    if (overflow || !valid_token_end(scanner, ch)) {
        return false;
    }

    if (negative) {
        *value = magnitude == (uint64_t)INT32_MAX + UINT64_C(1)
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
    InputScanner scanner;
    scanner_init(&scanner, stdin);

    size_t count;

    if (!read_size_value(&scanner, &count) ||
        count == 0 ||
        count > SIZE_MAX / sizeof(Tuple)) {
        return EXIT_FAILURE;
    }

    Tuple *tuples = malloc(count * sizeof(*tuples));

    if (tuples == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_int32_value(&scanner, &tuples[i].first) ||
            !read_int32_value(&scanner, &tuples[i].second)) {
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    int64_t maximum;

    if (!find_maximum_product(tuples, count, &maximum)) {
        free(tuples);
        return EXIT_FAILURE;
    }

    free(tuples);

    if (printf("%" PRId64 "\n", maximum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
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

static int scanner_get_byte(InputScanner *scanner)
{
    if (scanner == NULL || scanner->stream == NULL || scanner->failed) {
        return EOF;
    }

    if (scanner->position >= scanner->length) {
        scanner->position = 0;
        scanner->length = fread(scanner->buffer,
                                1,
                                sizeof scanner->buffer,
                                scanner->stream);

        if (ferror(scanner->stream)) {
            scanner->failed = true;
            scanner->length = 0;
            return EOF;
        }

        if (scanner->length == 0) {
            return EOF;
        }
    }

    return (int)scanner->buffer[scanner->position++];
}

static bool read_decimal_value(InputScanner *scanner,
                               bool allow_negative,
                               uintmax_t positive_limit,
                               uintmax_t negative_limit,
                               uintmax_t *magnitude,
                               bool *negative)
{
    int byte;
    uintmax_t result = 0;
    uintmax_t limit;
    bool is_negative = false;
    bool has_digit = false;
    bool valid = true;
    bool overflow = false;

    if (scanner == NULL || magnitude == NULL || negative == NULL) {
        return false;
    }

    do {
        byte = scanner_get_byte(scanner);
        if (byte == EOF) {
            return false;
        }
    } while (isspace((unsigned char)byte));

    if (byte == '+' || byte == '-') {
        is_negative = byte == '-';

        if (is_negative && !allow_negative) {
            valid = false;
        }

        byte = scanner_get_byte(scanner);
    }

    limit = is_negative ? negative_limit : positive_limit;

    while (byte != EOF && !isspace((unsigned char)byte)) {
        if (byte >= '0' && byte <= '9') {
            uintmax_t digit = (uintmax_t)(byte - '0');

            has_digit = true;

            if (!overflow) {
                if (result > limit / UINTMAX_C(10) ||
                    (result == limit / UINTMAX_C(10) &&
                     digit > limit % UINTMAX_C(10))) {
                    overflow = true;
                } else {
                    result = result * UINTMAX_C(10) + digit;
                }
            }
        } else {
            valid = false;
        }

        byte = scanner_get_byte(scanner);
    }

    if (scanner->failed || !has_digit || !valid || overflow) {
        return false;
    }

    *magnitude = result;
    *negative = is_negative;
    return true;
}

static bool read_size_value(InputScanner *scanner, size_t *value)
{
    uintmax_t magnitude;
    bool negative;

    if (value == NULL ||
        !read_decimal_value(scanner,
                            false,
                            (uintmax_t)SIZE_MAX,
                            (uintmax_t)SIZE_MAX,
                            &magnitude,
                            &negative)) {
        return false;
    }

    *value = (size_t)magnitude;
    return true;
}

static bool read_int32_value(InputScanner *scanner, int32_t *value)
{
    const uintmax_t positive_limit = (uintmax_t)INT32_MAX;
    const uintmax_t negative_limit =
        (uintmax_t)INT32_MAX + UINTMAX_C(1);
    uintmax_t magnitude;
    bool negative;

    if (value == NULL ||
        !read_decimal_value(scanner,
                            true,
                            positive_limit,
                            negative_limit,
                            &magnitude,
                            &negative)) {
        return false;
    }

    if (!negative) {
        *value = (int32_t)magnitude;
    } else if (magnitude == negative_limit) {
        *value = INT32_MIN;
    } else {
        *value = -(int32_t)magnitude;
    }

    return true;
}

static bool read_tuple(InputScanner *scanner, Tuple *tuple)
{
    if (scanner == NULL || tuple == NULL) {
        return false;
    }

    return read_int32_value(scanner, &tuple->first) &&
           read_int32_value(scanner, &tuple->second);
}

static int64_t tuple_product(const Tuple *tuple)
{
    return (int64_t)tuple->first * (int64_t)tuple->second;
}

int main(void)
{
    InputScanner scanner = {
        .stream = stdin,
        .buffer = {0},
        .position = 0,
        .length = 0,
        .failed = false
    };
    size_t count;
    Tuple tuple;
    int64_t maximum;

    if (!read_size_value(&scanner, &count) || count == 0) {
        fputs("Invalid tuple count\n", stderr);
        return EXIT_FAILURE;
    }

    if (!read_tuple(&scanner, &tuple)) {
        fputs("Invalid tuple input\n", stderr);
        return EXIT_FAILURE;
    }

    maximum = tuple_product(&tuple);

    for (size_t i = 1; i < count; ++i) {
        int64_t product;

        if (!read_tuple(&scanner, &tuple)) {
            fputs("Invalid tuple input\n", stderr);
            return EXIT_FAILURE;
        }

        product = tuple_product(&tuple);

        if (product > maximum) {
            maximum = product;
        }
    }

    if (printf("%" PRId64 "\n", maximum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
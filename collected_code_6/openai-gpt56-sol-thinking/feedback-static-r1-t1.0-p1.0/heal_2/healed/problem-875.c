#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <ctype.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

static int read_decimal(uintmax_t positive_limit,
                        uintmax_t negative_limit,
                        int allow_negative,
                        uintmax_t *magnitude,
                        int *negative)
{
    int character;
    int is_negative = 0;
    int has_digit = 0;
    int valid = 1;
    uintmax_t result = 0;
    uintmax_t limit;

    if (magnitude == NULL || negative == NULL) {
        return 0;
    }

    do {
        character = getchar();
    } while (character != EOF && isspace((unsigned char)character));

    if (character == EOF) {
        return 0;
    }

    if (character == '+' || character == '-') {
        is_negative = character == '-';

        if (is_negative && !allow_negative) {
            valid = 0;
        }

        character = getchar();
    }

    limit = is_negative ? negative_limit : positive_limit;

    while (character != EOF && !isspace((unsigned char)character)) {
        if (character >= '0' && character <= '9') {
            uintmax_t digit = (uintmax_t)(character - '0');

            has_digit = 1;

            if (result > (limit - digit) / UINTMAX_C(10)) {
                valid = 0;
            } else if (valid) {
                result = result * UINTMAX_C(10) + digit;
            }
        } else {
            valid = 0;
        }

        character = getchar();
    }

    if (character == EOF && ferror(stdin)) {
        return 0;
    }

    if (!valid || !has_digit) {
        return 0;
    }

    *magnitude = result;
    *negative = is_negative;
    return 1;
}

static int read_size(size_t *value)
{
    uintmax_t magnitude;
    int negative;

    if (value == NULL ||
        !read_decimal((uintmax_t)SIZE_MAX, 0, 0, &magnitude, &negative)) {
        return 0;
    }

    *value = (size_t)magnitude;
    return 1;
}

static int read_int64(int64_t *value)
{
    const uintmax_t positive_limit = (uintmax_t)INT64_MAX;
    const uintmax_t negative_limit = (uintmax_t)INT64_MAX + UINTMAX_C(1);
    uintmax_t magnitude;
    int negative;

    if (value == NULL ||
        !read_decimal(positive_limit, negative_limit, 1,
                      &magnitude, &negative)) {
        return 0;
    }

    if (!negative) {
        *value = (int64_t)magnitude;
    } else if (magnitude == negative_limit) {
        *value = INT64_MIN;
    } else {
        *value = -(int64_t)magnitude;
    }

    return 1;
}

static uint64_t absolute_difference(int64_t first, int64_t second)
{
    if (first >= second) {
        return (uint64_t)first - (uint64_t)second;
    }

    return (uint64_t)second - (uint64_t)first;
}

int main(void)
{
    size_t count;
    uint64_t minimum = UINT64_MAX;

    if (!read_size(&count) || count == 0) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        Tuple tuple;
        uint64_t difference;

        if (!read_int64(&tuple.first) || !read_int64(&tuple.second)) {
            return EXIT_FAILURE;
        }

        difference = absolute_difference(tuple.first, tuple.second);

        if (difference < minimum) {
            minimum = difference;
        }
    }

    if (printf("%" PRIu64 "\n", minimum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
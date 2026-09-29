#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <errno.h>
#include <ctype.h>

static uint64_t add_saturating(uint64_t a, uint64_t b)
{
    return b > UINT64_MAX - a ? UINT64_MAX : a + b;
}

static uint64_t mul2_saturating(uint64_t value)
{
    return value > UINT64_MAX / 2 ? UINT64_MAX : value * 2;
}

static int read_uint64(uint64_t *value)
{
    uintmax_t parsed = 0;
    int ch;
    int digit_seen = 0;
    int overflow = 0;

    if (value == NULL) {
        return 0;
    }

    do {
        ch = fgetc(stdin);
        if (ch == EOF) {
            return 0;
        }
    } while (ch != '\n' && isspace((unsigned char)ch));

    if (ch == '-') {
        while (ch != '\n' && ch != EOF) {
            ch = fgetc(stdin);
        }
        return 0;
    }

    if (ch == '+') {
        ch = fgetc(stdin);
    }

    while (ch != '\n' && ch != EOF && isdigit((unsigned char)ch)) {
        unsigned int digit = (unsigned int)(ch - '0');

        digit_seen = 1;
        if (parsed > (UINTMAX_MAX - digit) / 10) {
            overflow = 1;
        } else if (!overflow) {
            parsed = parsed * 10 + digit;
        }

        ch = fgetc(stdin);
    }

    while (ch != '\n' && ch != EOF && isspace((unsigned char)ch)) {
        ch = fgetc(stdin);
    }

    if (ch != '\n' && ch != EOF) {
        do {
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);
        return 0;
    }

    if (!digit_seen || overflow || parsed > UINT64_MAX) {
        return 0;
    }

    if (ch == EOF && ferror(stdin)) {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

static uint64_t count_subsequences_product_less_than_k(
    const uint64_t *array,
    size_t length,
    uint64_t k)
{
    uint64_t zero_count = 0;
    uint64_t positive_count = 0;
    uint64_t total_without_zeros = 1;

    if ((array == NULL && length != 0) || length == 0 || k == 0) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        if (array[i] == 0) {
            zero_count = add_saturating(zero_count, total_without_zeros);
        } else {
            if (array[i] < k) {
                positive_count =
                    add_saturating(positive_count, total_without_zeros);
            }

            total_without_zeros = mul2_saturating(total_without_zeros);
            zero_count = mul2_saturating(zero_count);
        }
    }

    return add_saturating(zero_count, positive_count);
}

int main(void)
{
    uint64_t input_length;
    uint64_t k;
    uint64_t result;
    uint64_t *array = NULL;
    size_t length;

    if (!read_uint64(&input_length) || !read_uint64(&k)) {
        return EXIT_FAILURE;
    }

    if (input_length > SIZE_MAX) {
        return EXIT_FAILURE;
    }

    length = (size_t)input_length;

    if (length > SIZE_MAX / sizeof *array) {
        return EXIT_FAILURE;
    }

    if (length != 0) {
        array = malloc(length * sizeof *array);
        if (array == NULL) {
            return EXIT_FAILURE;
        }

        for (size_t i = 0; i < length; ++i) {
            if (!read_uint64(&array[i])) {
                free(array);
                return EXIT_FAILURE;
            }
        }
    }

    result = count_subsequences_product_less_than_k(array, length, k);

    if (printf("%" PRIu64 "\n", result) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}
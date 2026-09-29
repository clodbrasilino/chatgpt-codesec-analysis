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
    char buffer[128];
    char *start;
    char *end;
    uintmax_t parsed;

    if (value == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        int ch;

        do {
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        return 0;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || parsed > UINT64_MAX) {
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
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
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <errno.h>
#include <ctype.h>

static int read_token(char **token)
{
    size_t length = 0;
    size_t capacity = 32;
    char *buffer;
    int ch;

    if (token == NULL) {
        return 0;
    }

    *token = NULL;

    do {
        ch = fgetc(stdin);
        if (ch == EOF) {
            return 0;
        }
    } while (isspace((unsigned char)ch));

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        if (length >= capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;

        ch = fgetc(stdin);
        if (ch == EOF) {
            if (ferror(stdin)) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (isspace((unsigned char)ch)) {
            break;
        }
    }

    buffer[length] = '\0';
    *token = buffer;
    return 1;
}

static int read_size(size_t *value)
{
    char *token;
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_token(&token)) {
        return 0;
    }

    if (token[0] == '\0' || token[0] == '-' || token[0] == '+') {
        free(token);
        return 0;
    }

    errno = 0;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        free(token);
        return 0;
    }

    *value = (size_t)parsed;
    free(token);
    return 1;
}

static int read_u64(uint64_t *value)
{
    char *token;
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_token(&token)) {
        return 0;
    }

    if (token[0] == '\0' || token[0] == '-' || token[0] == '+') {
        free(token);
        return 0;
    }

    errno = 0;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed > (uintmax_t)UINT64_MAX) {
        free(token);
        return 0;
    }

    *value = (uint64_t)parsed;
    free(token);
    return 1;
}

static int read_i64(int64_t *value)
{
    char *token;
    char *end;
    intmax_t parsed;

    if (value == NULL || !read_token(&token)) {
        return 0;
    }

    if (token[0] == '\0') {
        free(token);
        return 0;
    }

    errno = 0;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(token);
        return 0;
    }

    *value = (int64_t)parsed;
    free(token);
    return 1;
}

static int add_i64(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int multiply_i64_u64(int64_t a, uint64_t b, int64_t *result)
{
    uint64_t magnitude;
    uint64_t limit;
    uint64_t product;

    if (result == NULL) {
        return 0;
    }

    if (a == 0 || b == 0) {
        *result = 0;
        return 1;
    }

    if (a > 0) {
        if (b > (uint64_t)INT64_MAX / (uint64_t)a) {
            return 0;
        }

        *result = a * (int64_t)b;
        return 1;
    }

    magnitude = (uint64_t)(-(a + 1)) + UINT64_C(1);
    limit = (uint64_t)INT64_MAX + UINT64_C(1);

    if (b > limit / magnitude) {
        return 0;
    }

    product = magnitude * b;

    if (product == limit) {
        *result = INT64_MIN;
    } else {
        *result = -(int64_t)product;
    }

    return 1;
}

static int max_contiguous_sum_repeated(const int64_t *array,
                                       size_t length,
                                       uint64_t repetitions,
                                       int64_t *result)
{
    int64_t total = 0;
    int64_t prefix_sum = 0;
    int64_t suffix_sum = 0;
    int64_t max_prefix;
    int64_t max_suffix;
    int64_t current;
    int64_t best;
    int64_t combined;

    if (array == NULL || length == 0 || repetitions == 0 ||
        result == NULL) {
        return 0;
    }

    max_prefix = array[0];
    max_suffix = array[length - 1];
    current = array[0];
    best = array[0];

    for (size_t i = 0; i < length; ++i) {
        if (!add_i64(total, array[i], &total) ||
            !add_i64(prefix_sum, array[i], &prefix_sum)) {
            return 0;
        }

        if (prefix_sum > max_prefix) {
            max_prefix = prefix_sum;
        }

        if (i > 0) {
            if (current > 0) {
                if (!add_i64(current, array[i], &current)) {
                    return 0;
                }
            } else {
                current = array[i];
            }

            if (current > best) {
                best = current;
            }
        }

        if (!add_i64(suffix_sum, array[length - 1 - i], &suffix_sum)) {
            return 0;
        }

        if (suffix_sum > max_suffix) {
            max_suffix = suffix_sum;
        }
    }

    if (repetitions == 1) {
        *result = best;
        return 1;
    }

    if (!add_i64(max_suffix, max_prefix, &combined)) {
        return 0;
    }

    if (total > 0 && repetitions > 2) {
        int64_t middle;

        if (!multiply_i64_u64(total, repetitions - 2, &middle) ||
            !add_i64(combined, middle, &combined)) {
            return 0;
        }
    }

    *result = combined > best ? combined : best;
    return 1;
}

int main(void)
{
    size_t length;
    uint64_t repetitions;
    int64_t result;
    int64_t *array;

    if (!read_size(&length) ||
        !read_u64(&repetitions) ||
        length == 0 ||
        repetitions == 0 ||
        length > SIZE_MAX / sizeof(*array)) {
        return EXIT_FAILURE;
    }

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (!read_i64(&array[i])) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (!max_contiguous_sum_repeated(array, length, repetitions, &result)) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);

    if (printf("%" PRId64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
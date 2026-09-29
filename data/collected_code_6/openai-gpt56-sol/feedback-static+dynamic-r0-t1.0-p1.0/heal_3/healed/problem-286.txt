#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <errno.h>
#include <ctype.h>

static int read_token(char *buffer, size_t capacity)
{
    int ch;
    size_t length = 0;

    if (buffer == NULL || capacity < 2) {
        return 0;
    }

    do {
        ch = fgetc(stdin);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return 0;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length + 1 >= capacity) {
            do {
                ch = fgetc(stdin);
            } while (ch != EOF && !isspace((unsigned char)ch));
            return 0;
        }

        buffer[length++] = (char)ch;
        ch = fgetc(stdin);
    }

    buffer[length] = '\0';
    return 1;
}

static int read_size(size_t *value)
{
    char token[64];
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_token(token, sizeof(token)) ||
        token[0] == '-' || token[0] == '+') {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_u64(uint64_t *value)
{
    char token[64];
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_token(token, sizeof(token)) ||
        token[0] == '-' || token[0] == '+') {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

static int read_i64(int64_t *value)
{
    char token[64];
    char *end;
    intmax_t parsed;

    if (value == NULL || !read_token(token, sizeof(token))) {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static int add_i64(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL ||
        (b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int mul_i64_u64(int64_t a, uint64_t b, int64_t *result)
{
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
    } else {
        uint64_t magnitude = (uint64_t)(-(a + 1)) + UINT64_C(1);
        uint64_t limit = (uint64_t)INT64_MAX + UINT64_C(1);

        if (b > limit / magnitude) {
            return 0;
        }
    }

    if (b > (uint64_t)INT64_MAX) {
        if (a != -1 ||
            b != (uint64_t)INT64_MAX + UINT64_C(1)) {
            return 0;
        }

        *result = INT64_MIN;
        return 1;
    }

    *result = a * (int64_t)b;
    return 1;
}

static int max_contiguous_sum_repeated(const int64_t *array,
                                       size_t length,
                                       uint64_t repetitions,
                                       int64_t *result)
{
    int64_t total = 0;
    int64_t prefix = 0;
    int64_t max_prefix;
    int64_t suffix = 0;
    int64_t max_suffix;
    int64_t current;
    int64_t best;

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
            !add_i64(prefix, array[i], &prefix)) {
            return 0;
        }

        if (prefix > max_prefix) {
            max_prefix = prefix;
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

        if (!add_i64(suffix, array[length - 1 - i], &suffix)) {
            return 0;
        }

        if (suffix > max_suffix) {
            max_suffix = suffix;
        }
    }

    if (repetitions == 1) {
        *result = best;
        return 1;
    }

    int64_t combined;

    if (!add_i64(max_suffix, max_prefix, &combined)) {
        return 0;
    }

    if (total > 0 && repetitions > 2) {
        int64_t middle;

        if (!mul_i64_u64(total, repetitions - 2, &middle) ||
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
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <ctype.h>
#include <errno.h>

#define MAX_TOKEN_LENGTH 128U

static int read_token(char *buffer, size_t capacity)
{
    size_t length = 0U;
    int ch;
    int valid = 1;

    if (buffer == NULL || capacity < 2U) {
        return 0;
    }

    do {
        ch = getchar();
        if (ch == EOF) {
            buffer[0] = '\0';
            return 0;
        }
    } while (isspace((unsigned char)ch));

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length + 1U < capacity) {
            buffer[length++] = (char)ch;
        } else {
            valid = 0;
        }
        ch = getchar();
    }

    if (!valid) {
        buffer[0] = '\0';
        return 0;
    }

    buffer[length] = '\0';
    return 1;
}

static int read_uint64(uint64_t *value)
{
    char buffer[MAX_TOKEN_LENGTH];
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_token(buffer, sizeof(buffer))) {
        return 0;
    }

    if (buffer[0] == '\0' || buffer[0] == '-') {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE ||
        end == buffer ||
        end == NULL ||
        *end != '\0' ||
        parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

static int read_int64(int64_t *value)
{
    char buffer[MAX_TOKEN_LENGTH];
    char *end;
    intmax_t parsed;

    if (value == NULL || !read_token(buffer, sizeof(buffer))) {
        return 0;
    }

    if (buffer[0] == '\0') {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE ||
        end == buffer ||
        end == NULL ||
        *end != '\0' ||
        parsed < INT64_MIN ||
        parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static int64_t saturating_add(int64_t a, int64_t b)
{
    if (b > 0 && a > INT64_MAX - b) {
        return INT64_MAX;
    }

    if (b < 0 && a < INT64_MIN - b) {
        return INT64_MIN;
    }

    return a + b;
}

static int64_t saturating_multiply_positive(int64_t value, uint64_t factor)
{
    if (value <= 0 || factor == 0U) {
        return 0;
    }

    if (factor > (uint64_t)INT64_MAX) {
        return INT64_MAX;
    }

    if (value > INT64_MAX / (int64_t)factor) {
        return INT64_MAX;
    }

    return value * (int64_t)factor;
}

static int64_t max_subarray_repeated(const int64_t *array,
                                     size_t length,
                                     uint64_t repetitions)
{
    int64_t total = 0;
    int64_t prefix = INT64_MIN;
    int64_t suffix = INT64_MIN;
    int64_t best = INT64_MIN;
    int64_t running_prefix = 0;
    int64_t running_suffix = 0;
    int64_t current = INT64_MIN;

    for (size_t i = 0U; i < length; ++i) {
        total = saturating_add(total, array[i]);
        running_prefix = saturating_add(running_prefix, array[i]);

        if (running_prefix > prefix) {
            prefix = running_prefix;
        }

        if (current < 0) {
            current = array[i];
        } else {
            current = saturating_add(current, array[i]);
        }

        if (current > best) {
            best = current;
        }
    }

    for (size_t i = length; i > 0U; --i) {
        running_suffix = saturating_add(running_suffix, array[i - 1U]);

        if (running_suffix > suffix) {
            suffix = running_suffix;
        }
    }

    if (repetitions == 1U) {
        return best;
    }

    int64_t spanning = saturating_add(suffix, prefix);

    if (repetitions > 2U && total > 0) {
        int64_t middle_sum =
            saturating_multiply_positive(total, repetitions - 2U);
        spanning = saturating_add(spanning, middle_sum);
    }

    return best > spanning ? best : spanning;
}

int main(void)
{
    uint64_t input_length;
    uint64_t repetitions;
    size_t length;
    int64_t *array;
    int64_t result;

    if (!read_uint64(&input_length) ||
        !read_uint64(&repetitions) ||
        input_length == 0U ||
        repetitions == 0U ||
        input_length > (uint64_t)SIZE_MAX ||
        input_length > (uint64_t)(SIZE_MAX / sizeof(int64_t))) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    length = (size_t)input_length;
    array = malloc(length * sizeof(*array));

    if (array == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (!read_int64(&array[i])) {
            fputs("Invalid input\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    result = max_subarray_repeated(array, length, repetitions);

    if (printf("%" PRId64 "\n", result) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}
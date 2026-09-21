#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

static int read_token(char **buffer)
{
    size_t length = 0;
    size_t capacity = 32;
    char *token;
    int ch;

    if (buffer == NULL) {
        return 0;
    }

    *buffer = NULL;

    do {
        ch = fgetc(stdin);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return 0;
    }

    token = malloc(capacity);
    if (token == NULL) {
        return 0;
    }

    for (;;) {
        if (length >= capacity - 1) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(token);
                return 0;
            }

            new_capacity = capacity * 2;
            resized = realloc(token, new_capacity);
            if (resized == NULL) {
                free(token);
                return 0;
            }

            token = resized;
            capacity = new_capacity;
        }

        token[length++] = (char)ch;

        ch = fgetc(stdin);
        if (ch == EOF) {
            if (ferror(stdin)) {
                free(token);
                return 0;
            }
            break;
        }

        if (isspace((unsigned char)ch)) {
            break;
        }
    }

    token[length] = '\0';
    *buffer = token;
    return 1;
}

static int read_uintmax_value(uintmax_t *value)
{
    char *buffer = NULL;
    char *end = NULL;
    uintmax_t parsed;

    if (value == NULL || !read_token(&buffer)) {
        return 0;
    }

    if (buffer[0] == '\0' || buffer[0] == '-') {
        free(buffer);
        return 0;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0') {
        free(buffer);
        return 0;
    }

    free(buffer);
    *value = parsed;
    return 1;
}

static int read_int64_value(int64_t *value)
{
    char *buffer = NULL;
    char *end = NULL;
    intmax_t parsed;

    if (value == NULL || !read_token(&buffer)) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(buffer);
        return 0;
    }

    free(buffer);
    *value = (int64_t)parsed;
    return 1;
}

static int add_int64(int64_t a, int64_t b, int64_t *result)
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

static int multiply_nonnegative_int64(int64_t value, uint64_t multiplier,
                                      int64_t *result)
{
    uint64_t unsigned_value;

    if (result == NULL || value < 0) {
        return 0;
    }

    unsigned_value = (uint64_t)value;

    if (unsigned_value != 0 &&
        multiplier > (uint64_t)INT64_MAX / unsigned_value) {
        return 0;
    }

    *result = (int64_t)(unsigned_value * multiplier);
    return 1;
}

static int max_contiguous_sum_repeated(const int64_t *array, size_t length,
                                       uint64_t repetitions, int64_t *result)
{
    int64_t total = 0;
    int64_t prefix = 0;
    int64_t max_prefix = INT64_MIN;
    int64_t suffix = 0;
    int64_t max_suffix = INT64_MIN;
    int64_t current;
    int64_t best;
    int64_t combined;

    if (array == NULL || result == NULL || length == 0 || repetitions == 0) {
        return 0;
    }

    current = array[0];
    best = array[0];

    for (size_t i = 0; i < length; ++i) {
        if (!add_int64(total, array[i], &total) ||
            !add_int64(prefix, array[i], &prefix)) {
            return 0;
        }

        if (prefix > max_prefix) {
            max_prefix = prefix;
        }

        if (i > 0) {
            if (current > 0) {
                if (!add_int64(current, array[i], &current)) {
                    return 0;
                }
            } else {
                current = array[i];
            }

            if (current > best) {
                best = current;
            }
        }

        if (!add_int64(suffix, array[length - i - 1], &suffix)) {
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

    if (!add_int64(max_suffix, max_prefix, &combined)) {
        return 0;
    }

    if (total > 0 && repetitions > 2) {
        int64_t middle;

        if (!multiply_nonnegative_int64(total, repetitions - 2, &middle) ||
            !add_int64(combined, middle, &combined)) {
            return 0;
        }
    }

    *result = combined > best ? combined : best;
    return 1;
}

int main(void)
{
    uintmax_t length_input;
    uintmax_t repetitions_input;
    size_t length;
    uint64_t repetitions;
    int64_t *array;
    int64_t result;

    if (!read_uintmax_value(&length_input) ||
        !read_uintmax_value(&repetitions_input) ||
        length_input == 0 ||
        length_input > (uintmax_t)SIZE_MAX ||
        repetitions_input == 0 ||
        repetitions_input > (uintmax_t)UINT64_MAX) {
        return EXIT_FAILURE;
    }

    length = (size_t)length_input;
    repetitions = (uint64_t)repetitions_input;

    if (length > SIZE_MAX / sizeof(*array)) {
        return EXIT_FAILURE;
    }

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (!read_int64_value(&array[i])) {
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
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

static int read_token(char *buffer, size_t capacity)
{
    int ch;
    size_t length = 0;

    do {
        ch = getchar();
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return 0;
    }

    do {
        if (length + 1 >= capacity) {
            do {
                ch = getchar();
            } while (ch != EOF && !isspace((unsigned char)ch));
            return 0;
        }

        buffer[length++] = (char)ch;
        ch = getchar();
    } while (ch != EOF && !isspace((unsigned char)ch));

    buffer[length] = '\0';
    return 1;
}

static int read_uintmax_value(uintmax_t *value)
{
    char buffer[128];
    char *end;

    if (!read_token(buffer, sizeof(buffer)) || buffer[0] == '-') {
        return 0;
    }

    errno = 0;
    end = NULL;
    uintmax_t parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0') {
        return 0;
    }

    *value = parsed;
    return 1;
}

static int read_int64_value(int64_t *value)
{
    char buffer[128];
    char *end;

    if (!read_token(buffer, sizeof(buffer))) {
        return 0;
    }

    errno = 0;
    end = NULL;
    intmax_t parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static int add_int64(int64_t a, int64_t b, int64_t *result)
{
    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int multiply_int64_nonnegative(int64_t value, uint64_t multiplier,
                                      int64_t *result)
{
    if (value < 0 || multiplier > (uint64_t)INT64_MAX) {
        return 0;
    }

    if (value != 0 && multiplier > (uint64_t)INT64_MAX / (uint64_t)value) {
        return 0;
    }

    *result = value * (int64_t)multiplier;
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
    int64_t current = array[0];
    int64_t best = array[0];

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

        if (!add_int64(suffix, array[length - 1 - i], &suffix)) {
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

    if (!add_int64(max_suffix, max_prefix, &combined)) {
        return 0;
    }

    if (total > 0 && repetitions > 2) {
        int64_t middle;

        if (!multiply_int64_nonnegative(total, repetitions - 2, &middle) ||
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

    if (!read_uintmax_value(&length_input) ||
        !read_uintmax_value(&repetitions_input) ||
        length_input == 0 ||
        length_input > SIZE_MAX ||
        repetitions_input == 0 ||
        repetitions_input > UINT64_MAX) {
        return EXIT_FAILURE;
    }

    size_t length = (size_t)length_input;
    uint64_t repetitions = (uint64_t)repetitions_input;

    if (length > SIZE_MAX / sizeof(int64_t)) {
        return EXIT_FAILURE;
    }

    int64_t *array = malloc(length * sizeof(*array));

    if (array == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (!read_int64_value(&array[i])) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    int64_t result;

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
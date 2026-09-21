#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    FILE *stream;
    bool error;
    bool end_of_file;
} InputReader;

static int input_reader_get(InputReader *reader)
{
    if (reader == NULL || reader->stream == NULL ||
        reader->error || reader->end_of_file) {
        return EOF;
    }

    int character = fgetc(reader->stream);

    if (character == EOF) {
        if (ferror(reader->stream) != 0) {
            reader->error = true;
        } else if (feof(reader->stream) != 0) {
            reader->end_of_file = true;
        } else {
            reader->error = true;
        }
    }

    return character;
}

static bool checked_add_int64(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return false;
    }

    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return false;
    }

    *result = a + b;
    return true;
}

static bool checked_sub_int64(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return false;
    }

    if ((b > 0 && a < INT64_MIN + b) ||
        (b < 0 && a > INT64_MAX + b)) {
        return false;
    }

    *result = a - b;
    return true;
}

static bool read_first_non_space(InputReader *reader, int *character)
{
    if (reader == NULL || character == NULL) {
        return false;
    }

    int current;

    do {
        current = input_reader_get(reader);
        if (current == EOF) {
            return false;
        }
    } while (isspace((unsigned char)current) != 0);

    *character = current;
    return true;
}

static bool valid_token_ending(const InputReader *reader, int character)
{
    if (reader == NULL || reader->stream == NULL || reader->error) {
        return false;
    }

    if (character == EOF) {
        return reader->end_of_file;
    }

    return isspace((unsigned char)character) != 0;
}

static bool read_size_value(InputReader *reader, size_t *value)
{
    if (reader == NULL || value == NULL) {
        return false;
    }

    int character;

    if (!read_first_non_space(reader, &character) ||
        isdigit((unsigned char)character) == 0) {
        return false;
    }

    size_t parsed = 0;

    do {
        size_t digit = (size_t)(character - '0');

        if (parsed > (SIZE_MAX - digit) / (size_t)10) {
            return false;
        }

        parsed = parsed * (size_t)10 + digit;
        character = input_reader_get(reader);
    } while (character != EOF &&
             isdigit((unsigned char)character) != 0);

    if (!valid_token_ending(reader, character)) {
        return false;
    }

    *value = parsed;
    return true;
}

static bool read_int64_value(InputReader *reader, int64_t *value)
{
    if (reader == NULL || value == NULL) {
        return false;
    }

    int character;

    if (!read_first_non_space(reader, &character)) {
        return false;
    }

    bool negative = false;

    if (character == '+' || character == '-') {
        negative = character == '-';
        character = input_reader_get(reader);

        if (character == EOF) {
            return false;
        }
    }

    if (isdigit((unsigned char)character) == 0) {
        return false;
    }

    uint64_t magnitude = 0;
    uint64_t limit = (uint64_t)INT64_MAX;

    if (negative) {
        ++limit;
    }

    do {
        uint64_t digit = (uint64_t)(character - '0');

        if (magnitude > (limit - digit) / UINT64_C(10)) {
            return false;
        }

        magnitude = magnitude * UINT64_C(10) + digit;
        character = input_reader_get(reader);
    } while (character != EOF &&
             isdigit((unsigned char)character) != 0);

    if (!valid_token_ending(reader, character)) {
        return false;
    }

    if (negative) {
        if (magnitude == (uint64_t)INT64_MAX + UINT64_C(1)) {
            *value = INT64_MIN;
        } else {
            *value = -(int64_t)magnitude;
        }
    } else {
        *value = (int64_t)magnitude;
    }

    return true;
}

static bool allocate_int64_array(size_t length, int64_t **array)
{
    if (array == NULL) {
        return false;
    }

    *array = NULL;

    if (length == 0) {
        return true;
    }

    if (length > SIZE_MAX / sizeof **array) {
        return false;
    }

    *array = malloc(length * sizeof **array);
    return *array != NULL;
}

static bool max_sum_bitonic_subsequence(const int64_t *array,
                                        size_t length,
                                        int64_t *result)
{
    if (result == NULL) {
        return false;
    }

    if (length == 0) {
        *result = 0;
        return true;
    }

    if (array == NULL) {
        return false;
    }

    int64_t *increasing = NULL;
    int64_t *decreasing = NULL;
    bool success = false;

    if (!allocate_int64_array(length, &increasing) ||
        !allocate_int64_array(length, &decreasing)) {
        goto cleanup;
    }

    for (size_t i = 0; i < length; ++i) {
        increasing[i] = array[i];

        for (size_t j = 0; j < i; ++j) {
            if (array[j] >= array[i]) {
                continue;
            }

            int64_t candidate;

            if (!checked_add_int64(increasing[j], array[i], &candidate)) {
                if (increasing[j] > 0 && array[i] > 0) {
                    goto cleanup;
                }

                continue;
            }

            if (candidate > increasing[i]) {
                increasing[i] = candidate;
            }
        }
    }

    for (size_t i = length; i-- > 0;) {
        decreasing[i] = array[i];

        for (size_t j = i + 1; j < length; ++j) {
            if (array[j] >= array[i]) {
                continue;
            }

            int64_t candidate;

            if (!checked_add_int64(array[i], decreasing[j], &candidate)) {
                if (array[i] > 0 && decreasing[j] > 0) {
                    goto cleanup;
                }

                continue;
            }

            if (candidate > decreasing[i]) {
                decreasing[i] = candidate;
            }
        }
    }

    int64_t best = array[0];

    for (size_t i = 0; i < length; ++i) {
        int64_t tail;
        int64_t candidate;

        if (!checked_sub_int64(decreasing[i], array[i], &tail) ||
            !checked_add_int64(increasing[i], tail, &candidate)) {
            goto cleanup;
        }

        if (candidate > best) {
            best = candidate;
        }
    }

    *result = best;
    success = true;

cleanup:
    free(decreasing);
    free(increasing);
    return success;
}

int main(void)
{
    InputReader reader = {
        .stream = stdin,
        .error = false,
        .end_of_file = false
    };

    int64_t *array = NULL;
    int64_t result;
    size_t length;
    int status = EXIT_FAILURE;

    if (!read_size_value(&reader, &length)) {
        goto cleanup;
    }

    if (!allocate_int64_array(length, &array)) {
        goto cleanup;
    }

    for (size_t i = 0; i < length; ++i) {
        if (!read_int64_value(&reader, &array[i])) {
            goto cleanup;
        }
    }

    if (!max_sum_bitonic_subsequence(array, length, &result)) {
        goto cleanup;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        goto cleanup;
    }

    if (fflush(stdout) == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(array);
    return status;
}
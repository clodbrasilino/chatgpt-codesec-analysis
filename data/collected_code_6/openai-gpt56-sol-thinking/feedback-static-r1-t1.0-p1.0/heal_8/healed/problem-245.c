#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    INPUT_BUFFER_SIZE = 4096
};

typedef struct {
    FILE *file;
    unsigned char buffer[INPUT_BUFFER_SIZE];
    size_t position;
    size_t available;
    bool eof;
    bool error;
} InputStream;

static int input_get(InputStream *stream)
{
    if (stream == NULL || stream->file == NULL ||
        stream->error || stream->eof) {
        return EOF;
    }

    if (stream->position == stream->available) {
        stream->position = 0;
        stream->available = fread(stream->buffer, 1,
                                  sizeof(stream->buffer), stream->file);

        if (stream->available == 0) {
            if (ferror(stream->file)) {
                stream->error = true;
            } else {
                stream->eof = true;
            }
            return EOF;
        }
    }

    return (int)stream->buffer[stream->position++];
}

static bool is_input_space(int c)
{
    return c == ' ' || c == '\t' || c == '\n' ||
           c == '\r' || c == '\f' || c == '\v';
}

static bool read_size_value(InputStream *stream, size_t *value)
{
    if (stream == NULL || stream->file == NULL ||
        value == NULL || stream->error) {
        return false;
    }

    size_t parsed = 0;
    int c;

    do {
        c = input_get(stream);
    } while (is_input_space(c));

    if (c == '+') {
        c = input_get(stream);
    }

    if (c < '0' || c > '9') {
        return false;
    }

    do {
        size_t digit = (size_t)(c - '0');

        if (parsed > (SIZE_MAX - digit) / (size_t)10) {
            return false;
        }

        parsed = parsed * (size_t)10 + digit;
        c = input_get(stream);
    } while (c >= '0' && c <= '9');

    if (stream->error) {
        return false;
    }

    if (c != EOF && !is_input_space(c)) {
        return false;
    }

    *value = parsed;
    return true;
}

static bool read_int64_value(InputStream *stream, int64_t *value)
{
    if (stream == NULL || stream->file == NULL ||
        value == NULL || stream->error) {
        return false;
    }

    uint64_t magnitude = 0;
    bool negative = false;
    int c;

    do {
        c = input_get(stream);
    } while (is_input_space(c));

    if (c == '+' || c == '-') {
        negative = c == '-';
        c = input_get(stream);
    }

    if (c < '0' || c > '9') {
        return false;
    }

    const uint64_t limit = negative
        ? (uint64_t)INT64_MAX + UINT64_C(1)
        : (uint64_t)INT64_MAX;

    do {
        uint64_t digit = (uint64_t)(c - '0');

        if (magnitude > (limit - digit) / UINT64_C(10)) {
            return false;
        }

        magnitude = magnitude * UINT64_C(10) + digit;
        c = input_get(stream);
    } while (c >= '0' && c <= '9');

    if (stream->error) {
        return false;
    }

    if (c != EOF && !is_input_space(c)) {
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

bool max_sum_bitonic_subsequence(const int64_t *array, size_t length,
                                 int64_t *result)
{
    if (result == NULL) {
        return false;
    }

    if (length == 0) {
        *result = 0;
        return true;
    }

    if (array == NULL || length > SIZE_MAX / sizeof(*array)) {
        return false;
    }

    int64_t *increasing = malloc(length * sizeof(*increasing));
    if (increasing == NULL) {
        return false;
    }

    int64_t *decreasing = malloc(length * sizeof(*decreasing));
    if (decreasing == NULL) {
        free(increasing);
        return false;
    }

    bool success = false;

    for (size_t i = 0; i < length; ++i) {
        increasing[i] = array[i];

        for (size_t j = 0; j < i; ++j) {
            if (array[j] >= array[i]) {
                continue;
            }

            int64_t candidate;

            if (!checked_add_int64(increasing[j], array[i], &candidate)) {
                if (array[i] < 0) {
                    continue;
                }
                goto cleanup;
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
                if (decreasing[j] < 0) {
                    continue;
                }
                goto cleanup;
            }

            if (candidate > decreasing[i]) {
                decreasing[i] = candidate;
            }
        }
    }

    int64_t best = array[0];

    for (size_t i = 0; i < length; ++i) {
        int64_t decreasing_tail;
        int64_t candidate;

        if (!checked_sub_int64(decreasing[i], array[i],
                               &decreasing_tail)) {
            goto cleanup;
        }

        if (!checked_add_int64(increasing[i], decreasing_tail,
                               &candidate)) {
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
    InputStream input = {
        .file = stdin,
        .buffer = {0},
        .position = 0,
        .available = 0,
        .eof = false,
        .error = false
    };

    size_t length;
    int64_t *array = NULL;
    int64_t result;
    int status = EXIT_FAILURE;

    if (!read_size_value(&input, &length)) {
        goto cleanup;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        goto cleanup;
    }

    if (length != 0) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            goto cleanup;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (!read_int64_value(&input, &array[i])) {
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
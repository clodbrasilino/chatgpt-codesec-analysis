#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <ctype.h>
#include <errno.h>

static int read_token(char **token)
{
    char *buffer;
    size_t length = 0;
    size_t capacity = 32;
    int ch;

    if (token == NULL) {
        return 0;
    }

    *token = NULL;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
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
        if (length == capacity - 1) {
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

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
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

static int read_uint64(uint64_t *value)
{
    char *buffer;
    char *end;
    /* Possible weaknesses found:
     *  The scope of the variable 'parsed' can be reduced. [variableScope]
     */
    uintmax_t parsed;
    int valid = 0;

    if (value == NULL || !read_token(&buffer)) {
        return 0;
    }

    if (buffer[0] != '\0' && buffer[0] != '-') {
        errno = 0;
        parsed = strtoumax(buffer, &end, 10);

        if (errno != ERANGE &&
            end != buffer &&
            *end == '\0' &&
            parsed <= UINT64_MAX) {
            *value = (uint64_t)parsed;
            valid = 1;
        }
    }

    free(buffer);
    return valid;
}

static int read_int64(int64_t *value)
{
    char *buffer;
    char *end;
    /* Possible weaknesses found:
     *  The scope of the variable 'parsed' can be reduced. [variableScope]
     */
    intmax_t parsed;
    int valid = 0;

    if (value == NULL || !read_token(&buffer)) {
        return 0;
    }

    if (buffer[0] != '\0') {
        errno = 0;
        parsed = strtoimax(buffer, &end, 10);

        if (errno != ERANGE &&
            end != buffer &&
            *end == '\0' &&
            parsed >= INT64_MIN &&
            parsed <= INT64_MAX) {
            *value = (int64_t)parsed;
            valid = 1;
        }
    }

    free(buffer);
    return valid;
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

static int64_t saturating_multiply_positive(int64_t value, uint64_t count)
{
    if (value <= 0 || count == 0) {
        return 0;
    }

    if (count > (uint64_t)INT64_MAX) {
        return INT64_MAX;
    }

    if (value > INT64_MAX / (int64_t)count) {
        return INT64_MAX;
    }

    return value * (int64_t)count;
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

    for (size_t i = 0; i < length; ++i) {
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

    for (size_t i = length; i > 0; --i) {
        running_suffix = saturating_add(running_suffix, array[i - 1]);

        if (running_suffix > suffix) {
            suffix = running_suffix;
        }
    }

    if (repetitions == 1) {
        return best;
    }

    {
        int64_t spanning = saturating_add(suffix, prefix);

        if (repetitions > 2 && total > 0) {
            int64_t middle =
                saturating_multiply_positive(total, repetitions - 2);
            spanning = saturating_add(spanning, middle);
        }

        return best > spanning ? best : spanning;
    }
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
        input_length == 0 ||
        repetitions == 0 ||
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

    for (size_t i = 0; i < length; ++i) {
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
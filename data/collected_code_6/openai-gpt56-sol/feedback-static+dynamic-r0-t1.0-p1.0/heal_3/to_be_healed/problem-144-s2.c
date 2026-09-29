#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <ctype.h>
#include <errno.h>

static int compare_int64(const void *lhs, const void *rhs)
{
    const int64_t a = *(const int64_t *)lhs;
    const int64_t b = *(const int64_t *)rhs;

    return (a > b) - (a < b);
}

static int read_token(char **token)
{
    char *buffer;
    size_t length = 0;
    size_t capacity = 32;
    int ch;

    if (token == NULL) {
        return -1;
    }

    *token = NULL;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return -1;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    do {
        if (length == SIZE_MAX - 1) {
            free(buffer);
            return -1;
        }

        if (length + 1 >= capacity) {
            char *expanded;
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            expanded = realloc(buffer, new_capacity);
            if (expanded == NULL) {
                free(buffer);
                return -1;
            }

            buffer = expanded;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != EOF && !isspace((unsigned char)ch));

    buffer[length] = '\0';
    *token = buffer;
    return 0;
}

static int read_size(size_t *value)
{
    char *token;
    char *end;
    uintmax_t parsed;

    if (value == NULL || read_token(&token) != 0) {
        return -1;
    }

    if (token[0] == '-' || token[0] == '+') {
        free(token);
        return -1;
    }

    errno = 0;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed > SIZE_MAX) {
        free(token);
        return -1;
    }

    *value = (size_t)parsed;
    free(token);
    return 0;
}

static int read_int64(int64_t *value)
{
    char *token;
    char *end;
    intmax_t parsed;

    if (value == NULL || read_token(&token) != 0) {
        return -1;
    }

    errno = 0;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(token);
        return -1;
    }

    *value = (int64_t)parsed;
    free(token);
    return 0;
}

static int sum_absolute_differences(int64_t *array, size_t length,
                                    uint64_t *result)
{
    uint64_t sum = 0;
    uint64_t prefix = 0;
    int64_t previous;

    if (result == NULL || (length != 0 && array == NULL)) {
        return -1;
    }

    if (length == 0) {
        *result = 0;
        return 0;
    }

    if (length > UINT64_MAX) {
        return -1;
    }

    qsort(array, length, sizeof(*array), compare_int64);
    previous = array[0];

    for (size_t i = 1; i < length; ++i) {
        uint64_t current_bits = (uint64_t)array[i];
        uint64_t previous_bits = (uint64_t)previous;
        uint64_t delta = current_bits - previous_bits;
        uint64_t index = (uint64_t)i;
        uint64_t contribution;

        if (delta != 0 && index > UINT64_MAX / delta) {
            return -1;
        }

        contribution = delta * index;

        if (prefix > UINT64_MAX - contribution) {
            return -1;
        }

        prefix += contribution;

        if (sum > UINT64_MAX - prefix) {
            return -1;
        }

        sum += prefix;
        previous = array[i];
    }

    *result = sum;
    return 0;
}

int main(void)
{
    size_t length;
    int64_t *array = NULL;
    uint64_t result;

    if (read_size(&length) != 0) {
        fputs("Invalid array length\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        fputs("Array is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (length != 0) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (read_int64(&array[i]) != 0) {
            fputs("Invalid array element\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (sum_absolute_differences(array, length, &result) != 0) {
        fputs("Result exceeds supported range\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}
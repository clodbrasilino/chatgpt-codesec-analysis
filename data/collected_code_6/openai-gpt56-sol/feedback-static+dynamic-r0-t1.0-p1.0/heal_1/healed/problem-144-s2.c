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

static int read_token(char *buffer, size_t size)
{
    int ch;
    size_t length = 0;

    if (buffer == NULL || size < 2) {
        return -1;
    }

    do {
        ch = getchar();
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return -1;
    }

    do {
        if (length + 1 >= size) {
            while ((ch = getchar()) != EOF && !isspace((unsigned char)ch)) {
            }
            return -1;
        }

        buffer[length++] = (char)ch;
        ch = getchar();
    } while (ch != EOF && !isspace((unsigned char)ch));

    buffer[length] = '\0';
    return 0;
}

static int read_size(size_t *value)
{
    char token[64];
    char *end;
    uintmax_t parsed;

    if (value == NULL || read_token(token, sizeof(token)) != 0 ||
        token[0] == '-' || token[0] == '+') {
        return -1;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed > SIZE_MAX) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int read_int64(int64_t *value)
{
    char token[64];
    char *end;
    intmax_t parsed;

    if (value == NULL || read_token(token, sizeof(token)) != 0) {
        return -1;
    }

    errno = 0;
    end = NULL;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return -1;
    }

    *value = (int64_t)parsed;
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

    qsort(array, length, sizeof(*array), compare_int64);
    previous = array[0];

    for (size_t i = 1; i < length; ++i) {
        uint64_t delta;
        uint64_t contribution;
        uint64_t index;

        delta = (uint64_t)array[i] - (uint64_t)previous;
        index = (uint64_t)i;

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

    printf("%" PRIu64 "\n", result);
    free(array);
    return EXIT_SUCCESS;
}
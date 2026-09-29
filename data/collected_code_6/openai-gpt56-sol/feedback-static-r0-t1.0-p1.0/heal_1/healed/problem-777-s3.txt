#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <errno.h>

static int compare_int64(const void *lhs, const void *rhs)
{
    const int64_t a = *(const int64_t *)lhs;
    const int64_t b = *(const int64_t *)rhs;

    return (a > b) - (a < b);
}

static int read_size(size_t *value)
{
    char buffer[128];
    char *end = NULL;
    uintmax_t parsed;

    if (value == NULL || fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || parsed == 0 ||
        parsed > SIZE_MAX / sizeof(int64_t)) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n') {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int read_int64(int64_t *value)
{
    char token[128];
    char *end = NULL;
    intmax_t parsed;

    if (value == NULL || scanf("%127s", token) != 1) {
        return -1;
    }

    errno = 0;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return -1;
    }

    *value = (int64_t)parsed;
    return 0;
}

static int sum_non_repeated(const int64_t *array, size_t length, int64_t *sum)
{
    int64_t *copy;
    int64_t result = 0;
    size_t i = 0;

    if (array == NULL || sum == NULL || length == 0 ||
        length > SIZE_MAX / sizeof(*copy)) {
        return -1;
    }

    copy = malloc(length * sizeof(*copy));
    if (copy == NULL) {
        return -1;
    }

    for (size_t index = 0; index < length; ++index) {
        copy[index] = array[index];
    }

    qsort(copy, length, sizeof(*copy), compare_int64);

    while (i < length) {
        size_t j = i + 1;

        while (j < length && copy[j] == copy[i]) {
            ++j;
        }

        if (j - i == 1) {
            if ((copy[i] > 0 && result > INT64_MAX - copy[i]) ||
                (copy[i] < 0 && result < INT64_MIN - copy[i])) {
                free(copy);
                return -1;
            }

            result += copy[i];
        }

        i = j;
    }

    free(copy);
    *sum = result;
    return 0;
}

int main(void)
{
    size_t length;
    int64_t *array;
    int64_t sum;

    if (read_size(&length) != 0) {
        fputs("Invalid array length\n", stderr);
        return EXIT_FAILURE;
    }

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (read_int64(&array[i]) != 0) {
            fputs("Invalid array element\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (sum_non_repeated(array, length, &sum) != 0) {
        fputs("Unable to calculate sum\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", sum) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}
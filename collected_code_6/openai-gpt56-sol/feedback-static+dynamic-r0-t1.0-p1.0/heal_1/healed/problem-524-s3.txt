#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

static int read_int64(int64_t *value)
{
    char buffer[256];
    char *start;
    char *end;

    if (value == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return -1;
    }

    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        return -1;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    *value = strtoimax(start, &end, 10);
    if (start == end || errno == ERANGE) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    return *end == '\0' ? 0 : -1;
}

static int read_size(size_t *value)
{
    char buffer[256];
    char *start;
    char *end;
    uintmax_t parsed;

    if (value == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return -1;
    }

    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        return -1;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);
    if (start == end || errno == ERANGE || parsed > SIZE_MAX) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || parsed == 0) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int max_increasing_subsequence_sum(const int64_t *array,
                                          size_t length,
                                          int64_t *result)
{
    int64_t *sums;
    int64_t maximum;

    if (array == NULL || result == NULL || length == 0) {
        return -1;
    }

    if (length > SIZE_MAX / sizeof *sums) {
        return -1;
    }

    sums = malloc(length * sizeof *sums);
    if (sums == NULL) {
        return -1;
    }

    maximum = array[0];

    for (size_t i = 0; i < length; ++i) {
        sums[i] = array[i];

        for (size_t j = 0; j < i; ++j) {
            if (array[j] < array[i]) {
                if ((array[i] > 0 && sums[j] > INT64_MAX - array[i]) ||
                    (array[i] < 0 && sums[j] < INT64_MIN - array[i])) {
                    free(sums);
                    return -1;
                }

                int64_t candidate = sums[j] + array[i];

                if (candidate > sums[i]) {
                    sums[i] = candidate;
                }
            }
        }

        if (sums[i] > maximum) {
            maximum = sums[i];
        }
    }

    free(sums);
    *result = maximum;
    return 0;
}

int main(void)
{
    size_t length;
    int64_t *array;
    int64_t result;

    if (read_size(&length) != 0) {
        fprintf(stderr, "Invalid array length\n");
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof *array) {
        fprintf(stderr, "Array is too large\n");
        return EXIT_FAILURE;
    }

    array = malloc(length * sizeof *array);
    if (array == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (read_int64(&array[i]) != 0) {
            fprintf(stderr, "Invalid array element\n");
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (max_increasing_subsequence_sum(array, length, &result) != 0) {
        fprintf(stderr, "Unable to compute the result\n");
        free(array);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", result);
    free(array);
    return EXIT_SUCCESS;
}
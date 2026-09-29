#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

#define MAX_INPUT_LINE_LENGTH 4096

static int read_line(char **line)
{
    char *buffer;
    size_t length = 0;
    int ch;

    if (line == NULL) {
        return -1;
    }

    *line = NULL;

    buffer = malloc(MAX_INPUT_LINE_LENGTH + 1);
    if (buffer == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == MAX_INPUT_LINE_LENGTH) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);

            free(buffer);
            return -1;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return -1;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

static int read_int64(int64_t *value)
{
    char *buffer;
    char *start;
    char *end;
    intmax_t parsed;

    if (value == NULL || read_line(&buffer) != 0) {
        return -1;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    parsed = strtoimax(start, &end, 10);

    if (start == end || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(buffer);
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return -1;
    }

    *value = (int64_t)parsed;
    free(buffer);
    return 0;
}

static int read_size(size_t *value)
{
    char *buffer;
    char *start;
    char *end;
    uintmax_t parsed;

    if (value == NULL || read_line(&buffer) != 0) {
        return -1;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        free(buffer);
        return -1;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || parsed == 0 ||
        parsed > SIZE_MAX) {
        free(buffer);
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return -1;
    }

    *value = (size_t)parsed;
    free(buffer);
    return 0;
}

static int find_max_sum_increasing_subsequence(const int64_t *array,
                                                size_t length,
                                                int64_t *result)
{
    int64_t *sums;
    int64_t maximum;

    if (array == NULL || result == NULL || length == 0 ||
        length > SIZE_MAX / sizeof(*sums)) {
        return -1;
    }

    sums = malloc(length * sizeof(*sums));
    if (sums == NULL) {
        return -1;
    }

    maximum = array[0];

    for (size_t i = 0; i < length; ++i) {
        sums[i] = array[i];

        for (size_t j = 0; j < i; ++j) {
            int64_t candidate;

            if (array[j] >= array[i]) {
                continue;
            }

            if ((array[i] > 0 && sums[j] > INT64_MAX - array[i]) ||
                (array[i] < 0 && sums[j] < INT64_MIN - array[i])) {
                free(sums);
                return -1;
            }

            candidate = sums[j] + array[i];
            if (candidate > sums[i]) {
                sums[i] = candidate;
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
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (read_int64(&array[i]) != 0) {
            fputs("Invalid input\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (find_max_sum_increasing_subsequence(array, length, &result) != 0) {
        fputs("Unable to calculate result\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", result);
    free(array);
    return EXIT_SUCCESS;
}
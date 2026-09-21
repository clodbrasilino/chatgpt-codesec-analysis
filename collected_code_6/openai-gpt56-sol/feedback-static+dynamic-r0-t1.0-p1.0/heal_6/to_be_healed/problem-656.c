#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>

static int compare_int64(const void *lhs, const void *rhs)
{
    const int64_t a = *(const int64_t *)lhs;
    const int64_t b = *(const int64_t *)rhs;

    return (a > b) - (a < b);
}

static int read_line(char **line, size_t *capacity)
{
    size_t length = 0;

    if (line == NULL || capacity == NULL) {
        return -1;
    }

    if (*line == NULL || *capacity == 0) {
        size_t initial_capacity = 128;
        char *allocated = malloc(initial_capacity);

        if (allocated == NULL) {
            return -1;
        }

        *line = allocated;
        *capacity = initial_capacity;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                return -1;
            }
            break;
        }

        if (length > SIZE_MAX - 2) {
            return -1;
        }

        if (length + 1 >= *capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *resized;

            if (*capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = *capacity * 2;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            resized = realloc(*line, new_capacity);
            if (resized == NULL) {
                return -1;
            }

            *line = resized;
            *capacity = new_capacity;
        }

        (*line)[length++] = (char)ch;
    }

    (*line)[length] = '\0';
    return 0;
}

static int read_int64(int64_t *value)
{
    char *line = NULL;
    size_t capacity = 0;
    char *start;
    char *end;
    intmax_t parsed;
    int status = -1;

    if (value == NULL || read_line(&line, &capacity) != 0) {
        free(line);
        return -1;
    }

    start = line;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0') {
        goto cleanup;
    }

    errno = 0;
    parsed = strtoimax(start, &end, 10);

    if (start == end || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        goto cleanup;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        goto cleanup;
    }

    *value = (int64_t)parsed;
    status = 0;

cleanup:
    free(line);
    return status;
}

static int read_size(size_t *value)
{
    char *line = NULL;
    size_t capacity = 0;
    char *start;
    char *end;
    uintmax_t parsed;
    int status = -1;

    if (value == NULL || read_line(&line, &capacity) != 0) {
        free(line);
        return -1;
    }

    start = line;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        goto cleanup;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || parsed > SIZE_MAX) {
        goto cleanup;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        goto cleanup;
    }

    *value = (size_t)parsed;
    status = 0;

cleanup:
    free(line);
    return status;
}

static uint64_t absolute_difference(int64_t a, int64_t b)
{
    if (a >= b) {
        return (uint64_t)a - (uint64_t)b;
    }

    return (uint64_t)b - (uint64_t)a;
}

static int minimum_absolute_difference_sum(const int64_t *a,
                                           const int64_t *b,
                                           size_t length,
                                           uint64_t *result)
{
    int64_t *sorted_a = NULL;
    int64_t *sorted_b = NULL;
    uint64_t sum = 0;
    size_t allocation_size;
    size_t i;
    int status = -1;

    if (result == NULL || (length != 0 && (a == NULL || b == NULL))) {
        return -1;
    }

    if (length == 0) {
        *result = 0;
        return 0;
    }

    if (length > SIZE_MAX / sizeof(*sorted_a)) {
        return -1;
    }

    allocation_size = length * sizeof(*sorted_a);

    sorted_a = malloc(allocation_size);
    if (sorted_a == NULL) {
        goto cleanup;
    }

    sorted_b = malloc(allocation_size);
    if (sorted_b == NULL) {
        goto cleanup;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(sorted_a, a, allocation_size);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(sorted_b, b, allocation_size);

    qsort(sorted_a, length, sizeof(*sorted_a), compare_int64);
    qsort(sorted_b, length, sizeof(*sorted_b), compare_int64);

    for (i = 0; i < length; ++i) {
        uint64_t difference =
            absolute_difference(sorted_a[i], sorted_b[i]);

        if (sum > UINT64_MAX - difference) {
            goto cleanup;
        }

        sum += difference;
    }

    *result = sum;
    status = 0;

cleanup:
    free(sorted_a);
    free(sorted_b);
    return status;
}

int main(void)
{
    size_t length;
    int64_t *a = NULL;
    int64_t *b = NULL;
    uint64_t result;
    size_t i;
    int status = EXIT_FAILURE;

    if (read_size(&length) != 0) {
        fprintf(stderr, "Invalid array length.\n");
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*a)) {
        fprintf(stderr, "Array length is too large.\n");
        return EXIT_FAILURE;
    }

    if (length != 0) {
        size_t allocation_size = length * sizeof(*a);

        a = malloc(allocation_size);
        if (a == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            goto cleanup;
        }

        b = malloc(allocation_size);
        if (b == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            goto cleanup;
        }
    }

    for (i = 0; i < length; ++i) {
        if (read_int64(&a[i]) != 0) {
            fprintf(stderr, "Invalid element in the first array.\n");
            goto cleanup;
        }
    }

    for (i = 0; i < length; ++i) {
        if (read_int64(&b[i]) != 0) {
            fprintf(stderr, "Invalid element in the second array.\n");
            goto cleanup;
        }
    }

    if (minimum_absolute_difference_sum(a, b, length, &result) != 0) {
        fprintf(stderr, "Unable to calculate the result.\n");
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        fprintf(stderr, "Output error.\n");
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(a);
    free(b);
    return status;
}
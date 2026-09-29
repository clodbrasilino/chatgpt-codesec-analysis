#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <errno.h>
#include <ctype.h>

static int compare_int64(const void *left, const void *right)
{
    const int64_t a = *(const int64_t *)left;
    const int64_t b = *(const int64_t *)right;

    return (a > b) - (a < b);
}

static int read_token(char **token)
{
    char *buffer;
    size_t length = 0;
    size_t capacity = 32;
    int c;

    if (token == NULL) {
        return -1;
    }

    *token = NULL;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = getchar();
    } while (c != EOF && isspace((unsigned char)c));

    if (c == EOF) {
        return -1;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    while (c != EOF && !isspace((unsigned char)c)) {
        if (length == capacity - 1) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = getchar();
    }

    buffer[length] = '\0';
    *token = buffer;
    return 0;
}

static int read_size(size_t *value)
{
    char *buffer = NULL;
    char *end;
    uintmax_t parsed;
    int status = -1;

    if (value == NULL || read_token(&buffer) != 0) {
        return -1;
    }

    if (buffer[0] == '\0' || buffer[0] == '-') {
        goto cleanup;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > SIZE_MAX) {
        goto cleanup;
    }

    *value = (size_t)parsed;
    status = 0;

cleanup:
    free(buffer);
    return status;
}

static int read_int64(int64_t *value)
{
    char *buffer = NULL;
    char *end;
    intmax_t parsed;
    int status = -1;

    if (value == NULL || read_token(&buffer) != 0) {
        return -1;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        goto cleanup;
    }

    *value = (int64_t)parsed;
    status = 0;

cleanup:
    free(buffer);
    return status;
}

static int sum_absolute_differences(int64_t *values, size_t count,
                                    uint64_t *result)
{
    __int128 prefix_sum = 0;
    __int128 total = 0;

    if (result == NULL || (count != 0 && values == NULL)) {
        return -1;
    }

    if (count > 1) {
        qsort(values, count, sizeof(*values), compare_int64);
    }

    for (size_t i = 0; i < count; ++i) {
        const __int128 current = (__int128)values[i];
        const __int128 contribution =
            current * (__int128)i - prefix_sum;

        if (contribution < 0 ||
            contribution > (__int128)UINT64_MAX - total) {
            return -1;
        }

        total += contribution;
        prefix_sum += current;
    }

    *result = (uint64_t)total;
    return 0;
}

int main(void)
{
    size_t count;
    int64_t *values = NULL;
    uint64_t result;

    if (read_size(&count) != 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*values)) {
        fputs("Array size is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (count != 0) {
        values = malloc(count * sizeof(*values));
        if (values == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (read_int64(&values[i]) != 0) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (sum_absolute_differences(values, count, &result) != 0) {
        fputs("Result is out of range\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}
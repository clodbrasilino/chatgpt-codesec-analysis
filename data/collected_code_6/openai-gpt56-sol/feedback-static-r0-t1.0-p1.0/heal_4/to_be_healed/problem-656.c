#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>

static int compare_int64(const void *lhs, const void *rhs)
{
    const int64_t a = *(const int64_t *)lhs;
    const int64_t b = *(const int64_t *)rhs;

    return (a > b) - (a < b);
}

static int read_token(char **token)
{
    size_t capacity = 32U;
    size_t length = 0U;
    char *buffer;
    int ch;

    if (token == NULL) {
        return -1;
    }

    *token = NULL;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return ferror(stdin) ? -1 : 0;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length > SIZE_MAX - 2U) {
            free(buffer);
            return -1;
        }

        if (length + 1U >= capacity) {
            size_t required = length + 2U;
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2U) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2U;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    if (ch == EOF && ferror(stdin)) {
        free(buffer);
        return -1;
    }

    buffer[length] = '\0';
    *token = buffer;
    return 1;
}

static int read_size(size_t *value)
{
    char *buffer;
    char *end;
    uintmax_t parsed;
    int rc;

    if (value == NULL) {
        return -1;
    }

    rc = read_token(&buffer);
    if (rc != 1) {
        return -1;
    }

    if (buffer[0] == '\0' || buffer[0] == '-') {
        free(buffer);
        return -1;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        free(buffer);
        return -1;
    }

    *value = (size_t)parsed;
    free(buffer);
    return 0;
}

static int read_int64(int64_t *value)
{
    char *buffer;
    char *end;
    intmax_t parsed;
    int rc;

    if (value == NULL) {
        return -1;
    }

    rc = read_token(&buffer);
    if (rc != 1) {
        return -1;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(buffer);
        return -1;
    }

    *value = (int64_t)parsed;
    free(buffer);
    return 0;
}

static uint64_t absolute_difference(int64_t a, int64_t b)
{
    if (a >= b) {
        if (b < 0) {
            return (uint64_t)a + (uint64_t)(-(b + 1)) + UINT64_C(1);
        }
        return (uint64_t)(a - b);
    }

    if (a < 0) {
        return (uint64_t)b + (uint64_t)(-(a + 1)) + UINT64_C(1);
    }

    return (uint64_t)(b - a);
}

static int minimum_absolute_difference_sum(const int64_t *a,
                                           const int64_t *b,
                                           size_t length,
                                           uint64_t *result)
{
    int64_t *sorted_a = NULL;
    int64_t *sorted_b = NULL;
    uint64_t sum = 0U;
    size_t bytes;
    size_t i;

    if (result == NULL || (length != 0U && (a == NULL || b == NULL))) {
        return -1;
    }

    if (length == 0U) {
        *result = 0U;
        return 0;
    }

    if (length > SIZE_MAX / sizeof(*sorted_a)) {
        return -1;
    }

    bytes = length * sizeof(*sorted_a);

    sorted_a = malloc(bytes);
    sorted_b = malloc(bytes);
    if (sorted_a == NULL || sorted_b == NULL) {
        free(sorted_a);
        free(sorted_b);
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(sorted_a, a, bytes);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(sorted_b, b, bytes);

    qsort(sorted_a, length, sizeof(*sorted_a), compare_int64);
    qsort(sorted_b, length, sizeof(*sorted_b), compare_int64);

    for (i = 0U; i < length; ++i) {
        uint64_t difference =
            absolute_difference(sorted_a[i], sorted_b[i]);

        if (sum > UINT64_MAX - difference) {
            free(sorted_a);
            free(sorted_b);
            return -1;
        }

        sum += difference;
    }

    free(sorted_a);
    free(sorted_b);
    *result = sum;
    return 0;
}

int main(void)
{
    size_t length;
    size_t bytes;
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

    if (length != 0U) {
        bytes = length * sizeof(*a);
        a = malloc(bytes);
        b = malloc(bytes);

        if (a == NULL || b == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            goto cleanup;
        }
    }

    for (i = 0U; i < length; ++i) {
        if (read_int64(&a[i]) != 0) {
            fprintf(stderr, "Invalid element in the first array.\n");
            goto cleanup;
        }
    }

    for (i = 0U; i < length; ++i) {
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
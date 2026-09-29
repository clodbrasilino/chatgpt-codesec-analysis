#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

static int compare_int64(const void *left, const void *right)
{
    const int64_t a = *(const int64_t *)left;
    const int64_t b = *(const int64_t *)right;

    return (a > b) - (a < b);
}

static int read_token(char **token)
{
    size_t capacity = 32;
    size_t length = 0;
    char *buffer;
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
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return 0;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length == capacity - 1) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return 0;
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

    if (ferror(stdin)) {
        free(buffer);
        return 0;
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
    int success;

    if (value == NULL || !read_token(&buffer)) {
        return 0;
    }

    if (buffer[0] == '-' || buffer[0] == '+') {
        free(buffer);
        return 0;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    success = errno != ERANGE &&
              end != buffer &&
              *end == '\0' &&
              parsed != UINTMAX_C(0) &&
              parsed <= (uintmax_t)SIZE_MAX;

    if (success) {
        *value = (size_t)parsed;
    }

    free(buffer);
    return success;
}

static int read_int64(int64_t *value)
{
    char *buffer;
    char *end;
    intmax_t parsed;
    int success;

    if (value == NULL || !read_token(&buffer)) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    success = errno != ERANGE &&
              end != buffer &&
              *end == '\0' &&
              parsed >= (intmax_t)INT64_MIN &&
              parsed <= (intmax_t)INT64_MAX;

    if (success) {
        *value = (int64_t)parsed;
    }

    free(buffer);
    return success;
}

static uint64_t absolute_difference(int64_t a, int64_t b)
{
    uint64_t ua = (uint64_t)a;
    uint64_t ub = (uint64_t)b;

    return a >= b ? ua - ub : ub - ua;
}

static int calculate_operations(int64_t *values, size_t count,
                                uint64_t *operations)
{
    uint64_t total = UINT64_C(0);
    int64_t target;
    size_t i;

    if (values == NULL || operations == NULL || count == 0) {
        return 0;
    }

    qsort(values, count, sizeof(*values), compare_int64);
    target = values[count / 2];

    for (i = 0; i < count; ++i) {
        uint64_t difference = absolute_difference(values[i], target);

        if (difference > UINT64_MAX - total) {
            return 0;
        }

        total += difference;
    }

    *operations = total;
    return 1;
}

int main(void)
{
    size_t count;
    size_t i;
    int64_t *values;
    uint64_t operations;

    if (!read_size(&count) || count > SIZE_MAX / sizeof(*values)) {
        return EXIT_FAILURE;
    }

    values = malloc(count * sizeof(*values));
    if (values == NULL) {
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        if (!read_int64(&values[i])) {
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (!calculate_operations(values, count, &operations)) {
        free(values);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", operations) < 0) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}
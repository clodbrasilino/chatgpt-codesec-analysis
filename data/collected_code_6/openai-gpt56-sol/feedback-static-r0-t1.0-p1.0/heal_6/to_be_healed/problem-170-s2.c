#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

static bool read_token(char **token)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 32;
    int ch;

    if (token == NULL) {
        return false;
    }

    *token = NULL;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return false;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return false;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length == capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return false;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return false;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    }

    buffer[length] = '\0';
    *token = buffer;
    return true;
}

static bool read_size(size_t *value)
{
    char *buffer = NULL;
    char *end = NULL;
    uintmax_t parsed;
    bool valid;

    if (value == NULL || !read_token(&buffer)) {
        return false;
    }

    if (buffer[0] == '\0' || buffer[0] == '-' || buffer[0] == '+') {
        free(buffer);
        return false;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    valid = errno != ERANGE &&
            end != buffer &&
            *end == '\0' &&
            parsed <= SIZE_MAX;

    if (valid) {
        *value = (size_t)parsed;
    }

    free(buffer);
    return valid;
}

static bool read_int64(int64_t *value)
{
    char *buffer = NULL;
    char *end = NULL;
    intmax_t parsed;
    bool valid;

    if (value == NULL || !read_token(&buffer)) {
        return false;
    }

    if (buffer[0] == '\0') {
        free(buffer);
        return false;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    valid = errno != ERANGE &&
            end != buffer &&
            *end == '\0' &&
            parsed >= INT64_MIN &&
            parsed <= INT64_MAX;

    if (valid) {
        *value = (int64_t)parsed;
    }

    free(buffer);
    return valid;
}

static bool sum_range(const int64_t *list, size_t length, size_t first,
                      size_t last, int64_t *result)
{
    int64_t sum = 0;

    if (list == NULL || result == NULL || first > last || last >= length) {
        return false;
    }

    for (size_t i = first;; ++i) {
        if ((list[i] > 0 && sum > INT64_MAX - list[i]) ||
            (list[i] < 0 && sum < INT64_MIN - list[i])) {
            return false;
        }

        sum += list[i];

        if (i == last) {
            break;
        }
    }

    *result = sum;
    return true;
}

int main(void)
{
    size_t length;
    size_t first;
    size_t last;
    int64_t result;
    int64_t *list = NULL;
    int status = EXIT_FAILURE;

    if (!read_size(&length) || length == 0 ||
        length > SIZE_MAX / sizeof(*list)) {
        fprintf(stderr, "Invalid list length.\n");
        return EXIT_FAILURE;
    }

    list = malloc(length * sizeof(*list));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (!read_int64(&list[i])) {
            fprintf(stderr, "Invalid list element.\n");
            goto cleanup;
        }
    }

    if (!read_size(&first) || !read_size(&last)) {
        fprintf(stderr, "Invalid range.\n");
        goto cleanup;
    }

    if (!sum_range(list, length, first, last, &result)) {
        fprintf(stderr, "Invalid range or arithmetic overflow.\n");
        goto cleanup;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        fprintf(stderr, "Output error.\n");
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(list);
    return status;
}
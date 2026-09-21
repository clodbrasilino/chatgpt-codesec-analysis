#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <errno.h>
#include <ctype.h>

static int64_t max_value(int64_t a, int64_t b)
{
    return a > b ? a : b;
}

static int read_line(char **buffer, size_t *capacity)
{
    size_t length = 0;

    if (buffer == NULL || capacity == NULL) {
        return 0;
    }

    if (*buffer == NULL || *capacity < 2) {
        char *new_buffer = malloc(64);

        if (new_buffer == NULL) {
            return 0;
        }

        free(*buffer);
        *buffer = new_buffer;
        *capacity = 64;
    }

    for (;;) {
        int character;

        if (length + 1 >= *capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (*capacity > SIZE_MAX / 2) {
                return 0;
            }

            new_capacity = *capacity * 2;
            new_buffer = realloc(*buffer, new_capacity);

            if (new_buffer == NULL) {
                return 0;
            }

            *buffer = new_buffer;
            *capacity = new_capacity;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);

        if (character == '\n') {
            break;
        }

        if (character == EOF) {
            if (ferror(stdin) || length == 0) {
                return 0;
            }
            break;
        }

        (*buffer)[length++] = (char)character;
    }

    (*buffer)[length] = '\0';
    return 1;
}

static int read_int64(int64_t *value)
{
    char *buffer = NULL;
    size_t capacity = 0;
    char *start;
    char *end;
    intmax_t parsed;
    int valid = 0;

    if (value == NULL || !read_line(&buffer, &capacity)) {
        free(buffer);
        return 0;
    }

    start = buffer;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    parsed = strtoimax(start, &end, 10);

    if (end != start && errno != ERANGE &&
        parsed >= INT64_MIN && parsed <= INT64_MAX) {
        while (isspace((unsigned char)*end)) {
            ++end;
        }

        if (*end == '\0') {
            *value = (int64_t)parsed;
            valid = 1;
        }
    }

    free(buffer);
    return valid;
}

static int read_size(size_t *value)
{
    char *buffer = NULL;
    size_t capacity = 0;
    char *start;
    char *end;
    /* Possible weaknesses found:
     *  The scope of the variable 'parsed' can be reduced. [variableScope]
     */
    uintmax_t parsed;
    int valid = 0;

    if (value == NULL || !read_line(&buffer, &capacity)) {
        free(buffer);
        return 0;
    }

    start = buffer;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start != '\0' && *start != '-') {
        errno = 0;
        parsed = strtoumax(start, &end, 10);

        if (end != start && errno != ERANGE) {
            while (isspace((unsigned char)*end)) {
                ++end;
            }

            if (*end == '\0' &&
                parsed > 0 &&
                parsed <= SIZE_MAX &&
                parsed <= SIZE_MAX / sizeof(int64_t)) {
                *value = (size_t)parsed;
                valid = 1;
            }
        }
    }

    free(buffer);
    return valid;
}

static int maximum_non_adjacent_sum(const int64_t *top,
                                    const int64_t *bottom,
                                    size_t n,
                                    int64_t *result)
{
    int64_t excluded = 0;
    int64_t included = 0;

    if (top == NULL || bottom == NULL || result == NULL) {
        return 0;
    }

    for (size_t i = 0; i < n; ++i) {
        int64_t column_value = max_value(top[i], bottom[i]);
        int64_t next_excluded = max_value(excluded, included);
        int64_t next_included = 0;

        if (column_value > 0) {
            if (excluded > INT64_MAX - column_value) {
                return 0;
            }

            next_included = excluded + column_value;
        }

        excluded = next_excluded;
        included = next_included;
    }

    *result = max_value(excluded, included);
    return 1;
}

int main(void)
{
    size_t n;
    int64_t result;
    int64_t *top = NULL;
    int64_t *bottom = NULL;
    int status = EXIT_FAILURE;

    if (!read_size(&n)) {
        goto cleanup;
    }

    top = malloc(n * sizeof(*top));
    bottom = malloc(n * sizeof(*bottom));

    if (top == NULL || bottom == NULL) {
        goto cleanup;
    }

    for (size_t i = 0; i < n; ++i) {
        if (!read_int64(&top[i])) {
            goto cleanup;
        }
    }

    for (size_t i = 0; i < n; ++i) {
        if (!read_int64(&bottom[i])) {
            goto cleanup;
        }
    }

    if (!maximum_non_adjacent_sum(top, bottom, n, &result)) {
        goto cleanup;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(top);
    free(bottom);
    return status;
}
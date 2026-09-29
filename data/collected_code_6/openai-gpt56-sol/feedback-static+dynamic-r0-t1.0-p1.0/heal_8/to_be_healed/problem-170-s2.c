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
    size_t length = 0;
    size_t capacity = 32;
    char *buffer;
    int ch;

    if (token == NULL) {
        return false;
    }

    *token = NULL;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
        if (ch == EOF) {
            return false;
        }
    } while (isspace((unsigned char)ch));

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return false;
    }

    for (;;) {
        if (ch == EOF || isspace((unsigned char)ch)) {
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(buffer);
            return false;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return false;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return false;
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
        return false;
    }

    buffer[length] = '\0';
    *token = buffer;
    return true;
}

static bool read_size(size_t *value)
{
    char *buffer;
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_token(&buffer)) {
        return false;
    }

    if (buffer[0] == '\0' || buffer[0] == '-' || buffer[0] == '+') {
        free(buffer);
        return false;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || end == NULL || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        free(buffer);
        return false;
    }

    *value = (size_t)parsed;
    free(buffer);
    return true;
}

static bool read_int64(int64_t *value)
{
    char *buffer;
    char *end;
    intmax_t parsed;

    if (value == NULL || !read_token(&buffer)) {
        return false;
    }

    if (buffer[0] == '\0') {
        free(buffer);
        return false;
    }

    errno = 0;
    end = NULL;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || end == NULL || *end != '\0' ||
        parsed < (intmax_t)INT64_MIN || parsed > (intmax_t)INT64_MAX) {
        free(buffer);
        return false;
    }

    *value = (int64_t)parsed;
    free(buffer);
    return true;
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
    int64_t *list;

    if (!read_size(&length) || length == 0 ||
        length > SIZE_MAX / sizeof(*list)) {
        fputs("Invalid list length.\n", stderr);
        return EXIT_FAILURE;
    }

    list = malloc(length * sizeof(*list));
    if (list == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (!read_int64(&list[i])) {
            fputs("Invalid list element.\n", stderr);
            free(list);
            return EXIT_FAILURE;
        }
    }

    if (!read_size(&first) || !read_size(&last)) {
        fputs("Invalid range.\n", stderr);
        free(list);
        return EXIT_FAILURE;
    }

    if (!sum_range(list, length, first, last, &result)) {
        fputs("Invalid range or arithmetic overflow.\n", stderr);
        free(list);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        fputs("Output error.\n", stderr);
        free(list);
        return EXIT_FAILURE;
    }

    free(list);
    return EXIT_SUCCESS;
}
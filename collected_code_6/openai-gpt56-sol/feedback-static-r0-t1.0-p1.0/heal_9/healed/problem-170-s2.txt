#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

static bool read_token(char **token)
{
    char *buffer;
    size_t length = 0;
    size_t capacity = 32;
    int ch;

    if (token == NULL) {
        return false;
    }

    *token = NULL;

    do {
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
        if (length == SIZE_MAX - 1) {
            free(buffer);
            return false;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity <= length + 1) {
                free(buffer);
                return false;
            }

            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return false;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
        ch = getchar();
    }

    buffer[length] = '\0';
    *token = buffer;
    return true;
}

static bool read_size(size_t *value)
{
    char *buffer = NULL;
    char *end;
    uintmax_t parsed;
    bool valid = false;

    if (value == NULL || !read_token(&buffer)) {
        return false;
    }

    if (buffer[0] == '\0' || buffer[0] == '-' || buffer[0] == '+') {
        goto cleanup;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == 0 && end != buffer && *end == '\0' &&
        parsed <= (uintmax_t)SIZE_MAX) {
        *value = (size_t)parsed;
        valid = true;
    }

cleanup:
    free(buffer);
    return valid;
}

static bool read_int64(int64_t *value)
{
    char *buffer = NULL;
    char *end;
    intmax_t parsed;
    bool valid = false;

    if (value == NULL || !read_token(&buffer)) {
        return false;
    }

    if (buffer[0] == '\0') {
        goto cleanup;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == 0 && end != buffer && *end == '\0' &&
        parsed >= (intmax_t)INT64_MIN && parsed <= (intmax_t)INT64_MAX) {
        *value = (int64_t)parsed;
        valid = true;
    }

cleanup:
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
            goto cleanup;
        }
    }

    if (!read_size(&first) || !read_size(&last)) {
        fputs("Invalid range.\n", stderr);
        goto cleanup;
    }

    if (!sum_range(list, length, first, last, &result)) {
        fputs("Invalid range or arithmetic overflow.\n", stderr);
        goto cleanup;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        fputs("Output error.\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(list);
    return status;
}
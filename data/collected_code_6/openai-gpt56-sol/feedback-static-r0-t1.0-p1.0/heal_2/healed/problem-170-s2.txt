#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

static bool read_token(char *buffer, size_t size)
{
    size_t length = 0;
    int ch;

    if (buffer == NULL || size < 2) {
        return false;
    }

    do {
        ch = getchar();
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return false;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length >= size - 1) {
            do {
                ch = getchar();
            } while (ch != EOF && !isspace((unsigned char)ch));

            buffer[0] = '\0';
            return false;
        }

        buffer[length++] = (char)ch;
        ch = getchar();
    }

    buffer[length] = '\0';
    return true;
}

static bool read_size(size_t *value)
{
    char buffer[sizeof(uintmax_t) * CHAR_BIT + 2];
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_token(buffer, sizeof(buffer)) ||
        buffer[0] == '-') {
        return false;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        return false;
    }

    *value = (size_t)parsed;
    return true;
}

static bool read_int64(int64_t *value)
{
    char buffer[sizeof(intmax_t) * CHAR_BIT + 2];
    char *end;
    intmax_t parsed;

    if (value == NULL || !read_token(buffer, sizeof(buffer))) {
        return false;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed < (intmax_t)INT64_MIN || parsed > (intmax_t)INT64_MAX) {
        return false;
    }

    *value = (int64_t)parsed;
    return true;
}

static bool sum_range(const int64_t *list, size_t length, size_t first,
                      size_t last, int64_t *result)
{
    int64_t sum = 0;

    if (list == NULL || result == NULL || first > last || last >= length) {
        return false;
    }

    for (size_t i = first; i <= last; ++i) {
        if ((list[i] > 0 && sum > INT64_MAX - list[i]) ||
            (list[i] < 0 && sum < INT64_MIN - list[i])) {
            return false;
        }

        sum += list[i];
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
            free(list);
            return EXIT_FAILURE;
        }
    }

    if (!read_size(&first) || !read_size(&last)) {
        fprintf(stderr, "Invalid range.\n");
        free(list);
        return EXIT_FAILURE;
    }

    if (!sum_range(list, length, first, last, &result)) {
        fprintf(stderr, "Invalid range or arithmetic overflow.\n");
        free(list);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        fprintf(stderr, "Output error.\n");
        free(list);
        return EXIT_FAILURE;
    }

    free(list);
    return EXIT_SUCCESS;
}
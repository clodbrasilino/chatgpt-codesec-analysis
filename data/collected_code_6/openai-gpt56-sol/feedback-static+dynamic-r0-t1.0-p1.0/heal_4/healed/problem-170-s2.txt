#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

static bool read_token(char *buffer, size_t capacity)
{
    size_t length = 0;
    bool overflow = false;
    int ch;

    if (buffer == NULL || capacity < 2) {
        return false;
    }

    do {
        ch = fgetc(stdin);
        if (ch == EOF) {
            return false;
        }
    } while (isspace((unsigned char)ch));

    do {
        if (length < capacity - 1) {
            buffer[length++] = (char)ch;
        } else {
            overflow = true;
        }

        ch = fgetc(stdin);
    } while (ch != EOF && !isspace((unsigned char)ch));

    if (ferror(stdin) || overflow) {
        buffer[0] = '\0';
        return false;
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
        buffer[0] == '-' || buffer[0] == '+') {
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
    char buffer[sizeof(intmax_t) * CHAR_BIT + 3];
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
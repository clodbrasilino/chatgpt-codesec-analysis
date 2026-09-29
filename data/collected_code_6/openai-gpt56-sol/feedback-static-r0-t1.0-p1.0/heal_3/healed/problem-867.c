#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>

static int minimum_to_make_sum_even(const int64_t *array, size_t length,
                                    int64_t *result)
{
    unsigned int parity = 0U;

    if ((array == NULL && length != 0U) || result == NULL) {
        return 0;
    }

    for (size_t i = 0U; i < length; ++i) {
        parity ^= (unsigned int)((uint64_t)array[i] & UINT64_C(1));
    }

    *result = (int64_t)parity;
    return 1;
}

static int read_line(char **line)
{
    enum { BUFFER_SIZE = 4096 };
    char buffer[BUFFER_SIZE];
    size_t length;

    if (line == NULL) {
        return 0;
    }

    *line = NULL;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }

    length = strlen(buffer);

    if (length > 0U && buffer[length - 1U] == '\n') {
        buffer[--length] = '\0';

        if (length > 0U && buffer[length - 1U] == '\r') {
            buffer[--length] = '\0';
        }
    } else if (!feof(stdin)) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        return 0;
    }

    *line = malloc(length + 1U);
    if (*line == NULL) {
        return 0;
    }

    memcpy(*line, buffer, length + 1U);
    return 1;
}

static int valid_end(const char *end)
{
    if (end == NULL) {
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    return *end == '\0';
}

static int read_size(size_t *value)
{
    char *line = NULL;
    char *start;
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_line(&line)) {
        return 0;
    }

    start = line;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-' || *start == '\0') {
        free(line);
        return 0;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || parsed > SIZE_MAX ||
        !valid_end(end)) {
        free(line);
        return 0;
    }

    *value = (size_t)parsed;
    free(line);
    return 1;
}

static int read_int64(int64_t *value)
{
    char *line = NULL;
    char *start;
    char *end;
    intmax_t parsed;

    if (value == NULL || !read_line(&line)) {
        return 0;
    }

    start = line;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0') {
        free(line);
        return 0;
    }

    errno = 0;
    parsed = strtoimax(start, &end, 10);

    if (end == start || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX ||
        !valid_end(end)) {
        free(line);
        return 0;
    }

    *value = (int64_t)parsed;
    free(line);
    return 1;
}

int main(void)
{
    size_t length;
    int64_t *array = NULL;
    int64_t minimum;

    if (!read_size(&length)) {
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        return EXIT_FAILURE;
    }

    if (length != 0U) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            return EXIT_FAILURE;
        }

        for (size_t i = 0U; i < length; ++i) {
            if (!read_int64(&array[i])) {
                free(array);
                return EXIT_FAILURE;
            }
        }
    }

    if (!minimum_to_make_sum_even(array, length, &minimum)) {
        free(array);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", minimum) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}
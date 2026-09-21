#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

enum { MAX_LIST_SIZE = 1000000, MAX_INPUT_LINE = 128 };

static int read_line(char *buffer, size_t size)
{
    if (buffer == NULL || size < 2U) {
        return 0;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return 0;
    }

    size_t length = 0U;
    while (buffer[length] != '\0' && buffer[length] != '\n') {
        ++length;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
        return 1;
    }

    if (feof(stdin)) {
        return 1;
    }

    int ch;
    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return 0;
}

static int read_int64(int64_t *value)
{
    if (value == NULL) {
        return 0;
    }

    char line[MAX_INPUT_LINE];

    if (!read_line(line, sizeof line)) {
        return 0;
    }

    char *start = line;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    char *end = NULL;
    intmax_t parsed = strtoimax(start, &end, 10);

    if (start == end || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static int read_size(size_t *value)
{
    if (value == NULL) {
        return 0;
    }

    char line[MAX_INPUT_LINE];

    if (!read_line(line, sizeof line)) {
        return 0;
    }

    char *start = line;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        return 0;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t parsed = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || parsed > SIZE_MAX) {
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int add_consecutive_numbers(const int64_t *list, size_t length,
                                   int64_t *result)
{
    if ((list == NULL && length != 0U) || result == NULL) {
        return 0;
    }

    int64_t sum = 0;

    for (size_t i = 0U; i < length; ++i) {
        if ((list[i] > 0 && sum > INT64_MAX - list[i]) ||
            (list[i] < 0 && sum < INT64_MIN - list[i])) {
            return 0;
        }

        sum += list[i];
    }

    *result = sum;
    return 1;
}

int main(void)
{
    size_t length;

    if (!read_size(&length) || length > MAX_LIST_SIZE) {
        fputs("Invalid list length\n", stderr);
        return EXIT_FAILURE;
    }

    int64_t *list = NULL;

    if (length != 0U) {
        if (length > SIZE_MAX / sizeof *list) {
            fputs("List is too large\n", stderr);
            return EXIT_FAILURE;
        }

        list = malloc(length * sizeof *list);
        if (list == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0U; i < length; ++i) {
        if (!read_int64(&list[i])) {
            fputs("Invalid list element\n", stderr);
            free(list);
            return EXIT_FAILURE;
        }
    }

    int64_t sum;

    if (!add_consecutive_numbers(list, length, &sum)) {
        fputs("Arithmetic overflow\n", stderr);
        free(list);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", sum) < 0) {
        fputs("Output error\n", stderr);
        free(list);
        return EXIT_FAILURE;
    }

    free(list);
    return EXIT_SUCCESS;
}
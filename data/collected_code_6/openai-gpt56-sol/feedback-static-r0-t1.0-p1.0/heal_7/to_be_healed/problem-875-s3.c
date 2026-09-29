#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

static uint64_t absolute_difference(int64_t a, int64_t b)
{
    return a >= b
        ? (uint64_t)a - (uint64_t)b
        : (uint64_t)b - (uint64_t)a;
}

static int read_line(char **buffer, size_t *capacity)
{
    size_t length = 0;

    if (buffer == NULL || capacity == NULL) {
        return -1;
    }

    if (*buffer == NULL || *capacity < 2) {
        char *new_buffer = malloc(128);

        if (new_buffer == NULL) {
            return -1;
        }

        free(*buffer);
        *buffer = new_buffer;
        *capacity = 128;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = getchar();

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                return -1;
            }
            break;
        }

        if (length == *capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (*capacity > SIZE_MAX / 2) {
                return -1;
            }

            new_capacity = *capacity * 2;
            new_buffer = realloc(*buffer, new_capacity);

            if (new_buffer == NULL) {
                return -1;
            }

            *buffer = new_buffer;
            *capacity = new_capacity;
        }

        (*buffer)[length++] = (char)ch;
    }

    (*buffer)[length] = '\0';
    return 0;
}

static int only_whitespace(const char *text)
{
    if (text == NULL) {
        return 0;
    }

    while (*text != '\0') {
        if (!isspace((unsigned char)*text)) {
            return 0;
        }
        ++text;
    }

    return 1;
}

static int parse_count(const char *text, size_t *count)
{
    char *end;
    uintmax_t value;

    if (text == NULL || count == NULL) {
        return -1;
    }

    while (isspace((unsigned char)*text)) {
        ++text;
    }

    if (*text == '\0' || *text == '-' || *text == '+') {
        return -1;
    }

    errno = 0;
    value = strtoumax(text, &end, 10);

    if (end == text || errno == ERANGE || value == 0 ||
        value > SIZE_MAX || !only_whitespace(end)) {
        return -1;
    }

    *count = (size_t)value;
    return 0;
}

static int parse_tuple(const char *text, Tuple *tuple)
{
    char *end;
    intmax_t first;
    intmax_t second;

    if (text == NULL || tuple == NULL) {
        return -1;
    }

    while (isspace((unsigned char)*text)) {
        ++text;
    }

    if (*text == '\0') {
        return -1;
    }

    errno = 0;
    first = strtoimax(text, &end, 10);

    if (end == text || errno == ERANGE ||
        first < INT64_MIN || first > INT64_MAX) {
        return -1;
    }

    text = end;

    while (isspace((unsigned char)*text)) {
        ++text;
    }

    if (*text == '\0') {
        return -1;
    }

    errno = 0;
    second = strtoimax(text, &end, 10);

    if (end == text || errno == ERANGE ||
        second < INT64_MIN || second > INT64_MAX ||
        !only_whitespace(end)) {
        return -1;
    }

    tuple->first = (int64_t)first;
    tuple->second = (int64_t)second;
    return 0;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    size_t count;
    uint64_t minimum = 0;
    int status = EXIT_FAILURE;

    if (read_line(&line, &capacity) != 0 ||
        parse_count(line, &count) != 0) {
        goto cleanup;
    }

    for (size_t i = 0; i < count; ++i) {
        Tuple tuple;
        uint64_t difference;

        if (read_line(&line, &capacity) != 0 ||
            parse_tuple(line, &tuple) != 0) {
            goto cleanup;
        }

        difference = absolute_difference(tuple.first, tuple.second);

        if (i == 0 || difference < minimum) {
            minimum = difference;
        }
    }

    if (printf("%" PRIu64 "\n", minimum) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(line);
    return status;
}
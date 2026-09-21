#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

static int are_reverses(const char *first, size_t first_length,
                        const char *second, size_t second_length)
{
    size_t i;

    if (first == NULL || second == NULL || first_length != second_length) {
        return 0;
    }

    for (i = 0; i < first_length; ++i) {
        if (first[i] != second[first_length - i - 1U]) {
            return 0;
        }
    }

    return 1;
}

static int count_reverse_pairs(const char *const strings[],
                               const size_t lengths[],
                               size_t count, size_t *pairs)
{
    size_t total = 0;
    size_t i;
    size_t j;

    if (strings == NULL || lengths == NULL || pairs == NULL) {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        for (j = i + 1U; j < count; ++j) {
            if (are_reverses(strings[i], lengths[i],
                             strings[j], lengths[j])) {
                if (total == SIZE_MAX) {
                    return -1;
                }
                ++total;
            }
        }
    }

    *pairs = total;
    return 0;
}

static int read_count(FILE *stream, size_t *count)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    uintmax_t value;
    int result = -1;

    if (stream == NULL || count == NULL) {
        return -1;
    }

    length = getline(&line, &capacity, stream);
    if (length < 0) {
        goto cleanup;
    }

    if (length > 0 && line[(size_t)length - 1U] == '\n') {
        line[--length] = '\0';
    }

    if (length > 0 && line[(size_t)length - 1U] == '\r') {
        line[--length] = '\0';
    }

    if (length == 0 || line[0] == '-') {
        goto cleanup;
    }

    errno = 0;
    end = NULL;
    value = strtoumax(line, &end, 10);

    if (errno == ERANGE || end == line || end == NULL || value > SIZE_MAX) {
        goto cleanup;
    }

    while (*end == ' ' || *end == '\t' ||
           *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        goto cleanup;
    }

    *count = (size_t)value;
    result = 0;

cleanup:
    free(line);
    return result;
}

static int duplicate_bytes(char **destination, const char *source,
                           size_t source_size, size_t length)
{
    char *copy;

    if (destination == NULL || source == NULL ||
        length > source_size || length == SIZE_MAX) {
        return -1;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return -1;
    }

    if (length > 0U) {
        memcpy(copy, source, length);
    }

    copy[length] = '\0';
    *destination = copy;
    return 0;
}

int main(void)
{
    char **strings = NULL;
    size_t *lengths = NULL;
    char *line = NULL;
    size_t line_capacity = 0;
    size_t count = 0;
    size_t initialized = 0;
    size_t pairs = 0;
    size_t i;
    ssize_t input_length;
    int status = EXIT_FAILURE;

    if (read_count(stdin, &count) != 0) {
        goto cleanup;
    }

    if (count > 0U) {
        if (count > SIZE_MAX / sizeof *strings ||
            count > SIZE_MAX / sizeof *lengths) {
            goto cleanup;
        }

        strings = calloc(count, sizeof *strings);
        lengths = calloc(count, sizeof *lengths);

        if (strings == NULL || lengths == NULL) {
            goto cleanup;
        }
    }

    for (i = 0; i < count; ++i) {
        size_t input_size;
        size_t string_length;

        input_length = getline(&line, &line_capacity, stdin);
        if (input_length < 0) {
            goto cleanup;
        }

        input_size = (size_t)input_length;
        string_length = input_size;

        if (string_length > 0U && line[string_length - 1U] == '\n') {
            --string_length;
        }

        if (string_length > 0U && line[string_length - 1U] == '\r') {
            --string_length;
        }

        if (duplicate_bytes(&strings[i], line, input_size,
                            string_length) != 0) {
            goto cleanup;
        }

        lengths[i] = string_length;
        ++initialized;
    }

    if (count_reverse_pairs((const char *const *)strings, lengths,
                            count, &pairs) != 0) {
        goto cleanup;
    }

    if (printf("%zu\n", pairs) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(line);

    for (i = 0; i < initialized; ++i) {
        free(strings[i]);
    }

    free(lengths);
    free(strings);

    return status;
}
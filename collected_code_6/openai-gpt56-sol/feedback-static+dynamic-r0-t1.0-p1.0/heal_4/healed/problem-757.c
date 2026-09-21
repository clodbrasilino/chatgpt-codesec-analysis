#define _POSIX_C_SOURCE 200809L

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

static int are_reverses(const char *first, size_t first_length,
                        const char *second, size_t second_length)
{
    if (first == NULL || second == NULL || first_length != second_length) {
        return 0;
    }

    for (size_t i = 0; i < first_length; ++i) {
        if (first[i] != second[first_length - i - 1U]) {
            return 0;
        }
    }

    return 1;
}

static size_t count_reverse_pairs(const char *const strings[],
                                  const size_t lengths[],
                                  size_t count)
{
    size_t pairs = 0;

    if (strings == NULL || lengths == NULL) {
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        for (size_t j = i + 1U; j < count; ++j) {
            if (are_reverses(strings[i], lengths[i],
                             strings[j], lengths[j])) {
                if (pairs == SIZE_MAX) {
                    return SIZE_MAX;
                }
                ++pairs;
            }
        }
    }

    return pairs;
}

static int read_count(size_t *count)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    uintmax_t value;

    if (count == NULL) {
        return 0;
    }

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return 0;
    }

    if (length > 0 && line[(size_t)length - 1U] == '\n') {
        line[--length] = '\0';
    }

    if (length > 0 && line[(size_t)length - 1U] == '\r') {
        line[--length] = '\0';
    }

    if (length == 0 || line[0] == '-') {
        free(line);
        return 0;
    }

    end = NULL;
    value = strtoumax(line, &end, 10);

    if (end == line || *end != '\0' || value > SIZE_MAX) {
        free(line);
        return 0;
    }

    *count = (size_t)value;
    free(line);
    return 1;
}

int main(void)
{
    char **strings = NULL;
    size_t *lengths = NULL;
    char *line = NULL;
    size_t line_capacity = 0;
    size_t count = 0;
    size_t initialized = 0;
    size_t pairs;
    int status = EXIT_FAILURE;

    if (!read_count(&count)) {
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*strings) ||
        count > SIZE_MAX / sizeof(*lengths)) {
        return EXIT_FAILURE;
    }

    if (count != 0U) {
        strings = calloc(count, sizeof(*strings));
        lengths = calloc(count, sizeof(*lengths));

        if (strings == NULL || lengths == NULL) {
            goto cleanup;
        }
    }

    while (initialized < count) {
        ssize_t input_length;
        size_t length;
        char *copy;

        input_length = getline(&line, &line_capacity, stdin);
        if (input_length < 0) {
            goto cleanup;
        }

        length = (size_t)input_length;

        if (length > 0U && line[length - 1U] == '\n') {
            --length;
        }

        if (length > 0U && line[length - 1U] == '\r') {
            --length;
        }

        if (length == SIZE_MAX) {
            goto cleanup;
        }

        copy = malloc(length + 1U);
        if (copy == NULL) {
            goto cleanup;
        }

        if (length != 0U) {
            memcpy(copy, line, length);
        }
        copy[length] = '\0';

        strings[initialized] = copy;
        lengths[initialized] = length;
        ++initialized;
    }

    pairs = count_reverse_pairs((const char *const *)strings, lengths, count);

    if (printf("%zu\n", pairs) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(line);

    while (initialized > 0U) {
        free(strings[--initialized]);
    }

    free(lengths);
    free(strings);

    return status;
}
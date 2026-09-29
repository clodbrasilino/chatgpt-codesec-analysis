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
    ssize_t input_length;
    size_t length;
    char *end;
    uintmax_t value;
    int valid = 0;

    if (count == NULL) {
        return 0;
    }

    input_length = getline(&line, &capacity, stdin);
    if (input_length < 0) {
        goto cleanup;
    }

    length = (size_t)input_length;

    if (length > 0U && line[length - 1U] == '\n') {
        line[--length] = '\0';
    }

    if (length > 0U && line[length - 1U] == '\r') {
        line[--length] = '\0';
    }

    if (length == 0U || line[0] == '-') {
        goto cleanup;
    }

    errno = 0;
    end = NULL;
    value = strtoumax(line, &end, 10);

    if (errno == ERANGE || end == line || end == NULL || *end != '\0' ||
        value > (uintmax_t)SIZE_MAX) {
        goto cleanup;
    }

    *count = (size_t)value;
    valid = 1;

cleanup:
    free(line);
    return valid;
}

static char *duplicate_bytes(const char *source, size_t length)
{
    char *destination;

    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    destination = malloc(length + 1U);
    if (destination == NULL) {
        return NULL;
    }

    if (length > 0U) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(destination, source, length);
    }

    destination[length] = '\0';
    return destination;
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

    if (count > 0U) {
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

        copy = duplicate_bytes(line, length);
        if (copy == NULL) {
            goto cleanup;
        }

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
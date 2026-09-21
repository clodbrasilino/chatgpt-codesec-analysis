#define _POSIX_C_SOURCE 200809L

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

static size_t count_reverse_pairs(const char *const strings[],
                                  const size_t lengths[],
                                  size_t count)
{
    size_t pairs = 0;
    size_t i;
    size_t j;

    if (strings == NULL || lengths == NULL) {
        return 0;
    }

    for (i = 0; i < count; ++i) {
        for (j = i + 1U; j < count; ++j) {
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

static int discard_line(FILE *stream)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[4096];

    for (;;) {
        if (fgets(buffer, sizeof buffer, stream) == NULL) {
            return feof(stream) ? 0 : -1;
        }

        if (strchr(buffer, '\n') != NULL) {
            return 1;
        }
    }
}

int main(void)
{
    char **strings = NULL;
    size_t *lengths = NULL;
    char *line = NULL;
    size_t line_capacity = 0;
    size_t count = 0;
    size_t initialized = 0;
    size_t i;
    size_t pairs;
    ssize_t input_length;
    int discard_result;
    int status = EXIT_FAILURE;

    if (scanf("%zu", &count) != 1) {
        goto cleanup;
    }

    discard_result = discard_line(stdin);
    if (discard_result < 0 || (discard_result == 0 && count != 0U)) {
        goto cleanup;
    }

    if (count != 0U) {
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
        size_t string_length;

        input_length = getline(&line, &line_capacity, stdin);
        if (input_length < 0) {
            goto cleanup;
        }

        string_length = (size_t)input_length;

        if (string_length > 0U && line[string_length - 1U] == '\n') {
            --string_length;
        }

        if (string_length > 0U && line[string_length - 1U] == '\r') {
            --string_length;
        }

        if (string_length == SIZE_MAX) {
            goto cleanup;
        }

        strings[i] = malloc(string_length + 1U);
        if (strings[i] == NULL) {
            goto cleanup;
        }

        if (string_length > 0U) {
            memmove(strings[i], line, string_length);
        }

        strings[i][string_length] = '\0';
        lengths[i] = string_length;
        ++initialized;
    }

    pairs = count_reverse_pairs((const char *const *)strings, lengths, count);

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
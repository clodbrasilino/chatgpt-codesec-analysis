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

static size_t count_reverse_pairs(char *const strings[],
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

int main(void)
{
    char **strings = NULL;
    size_t *lengths = NULL;
    char *line = NULL;
    size_t line_capacity = 0;
    size_t count;
    size_t initialized = 0;
    size_t pairs;
    int ch;
    int status = EXIT_FAILURE;

    if (scanf("%zu", &count) != 1) {
        return EXIT_FAILURE;
    }

    do {
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    if (ch == EOF && count != 0U) {
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

        strings[initialized] = malloc(length + 1U);
        if (strings[initialized] == NULL) {
            goto cleanup;
        }

        for (size_t i = 0; i < length; ++i) {
            strings[initialized][i] = line[i];
        }

        strings[initialized][length] = '\0';
        lengths[initialized] = length;
        ++initialized;
    }

    pairs = count_reverse_pairs(strings, lengths, count);

    if (printf("%zu\n", pairs) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(line);

    while (initialized > 0U) {
        --initialized;
        free(strings[initialized]);
    }

    free(lengths);
    free(strings);

    return status;
}
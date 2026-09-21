#define _POSIX_C_SOURCE 200809L

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

static int are_reverses(const char *first, const char *second)
{
    size_t first_length;
    size_t second_length;
    size_t i;

    if (first == NULL || second == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    first_length = strlen(first);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    second_length = strlen(second);

    if (first_length != second_length) {
        return 0;
    }

    for (i = 0; i < first_length; ++i) {
        if (first[i] != second[first_length - i - 1U]) {
            return 0;
        }
    }

    return 1;
}

static size_t count_reverse_pairs(const char *const strings[], size_t count)
{
    size_t pairs = 0;
    size_t i;
    size_t j;

    if (strings == NULL) {
        return 0;
    }

    for (i = 0; i < count; ++i) {
        for (j = i + 1U; j < count; ++j) {
            if (are_reverses(strings[i], strings[j])) {
                ++pairs;
            }
        }
    }

    return pairs;
}

int main(void)
{
    char **strings = NULL;
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
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    if (ch == EOF && count != 0U) {
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*strings)) {
        return EXIT_FAILURE;
    }

    if (count != 0U) {
        strings = calloc(count, sizeof(*strings));
        if (strings == NULL) {
            return EXIT_FAILURE;
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

        if (length != 0U && line[length - 1U] == '\n') {
            line[--length] = '\0';
        }

        if (length != 0U && line[length - 1U] == '\r') {
            line[--length] = '\0';
        }

        if (length == SIZE_MAX) {
            goto cleanup;
        }

        strings[initialized] = malloc(length + 1U);
        if (strings[initialized] == NULL) {
            goto cleanup;
        }

        if (length != 0U) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(strings[initialized], line, length);
        }
        strings[initialized][length] = '\0';
        ++initialized;
    }

    pairs = count_reverse_pairs((const char *const *)strings, count);

    if (printf("%zu\n", pairs) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(line);

    while (initialized != 0U) {
        free(strings[--initialized]);
    }

    free(strings);
    return status;
}
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
    size_t capacity = 0;
    size_t count;
    size_t i;
    size_t pairs;
    ssize_t length;
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

    if (count > 0U) {
        if (count > SIZE_MAX / sizeof(*strings)) {
            return EXIT_FAILURE;
        }

        strings = calloc(count, sizeof(*strings));
        if (strings == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < count; ++i) {
        size_t string_length;

        length = getline(&line, &capacity, stdin);
        if (length < 0) {
            goto cleanup;
        }

        string_length = (size_t)length;

        if (string_length > 0U && line[string_length - 1U] == '\n') {
            line[--string_length] = '\0';
        }

        if (string_length > 0U && line[string_length - 1U] == '\r') {
            line[--string_length] = '\0';
        }

        if (string_length == SIZE_MAX) {
            goto cleanup;
        }

        strings[i] = malloc(string_length + 1U);
        if (strings[i] == NULL) {
            goto cleanup;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(strings[i], line, string_length);
        strings[i][string_length] = '\0';
    }

    pairs = count_reverse_pairs((const char *const *)strings, count);

    if (printf("%zu\n", pairs) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(line);

    for (i = 0; i < count; ++i) {
        free(strings[i]);
    }

    free(strings);
    return status;
}
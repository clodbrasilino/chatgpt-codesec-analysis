#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void free_strings(char **strings, size_t count)
{
    size_t i;

    if (strings == NULL) {
        return;
    }

    for (i = 0U; i < count; ++i) {
        free(strings[i]);
    }

    free(strings);
}

static int append_string(char ***strings, size_t *count,
                         const char *start, const char *end)
{
    char **resized;
    char *value;
    size_t length;
    size_t new_count;

    if (strings == NULL || count == NULL || start == NULL || end == NULL ||
        end < start) {
        return -1;
    }

    length = (size_t)(end - start);

    if (length == SIZE_MAX || *count == SIZE_MAX) {
        return -1;
    }

    new_count = *count + 1U;

    if (new_count > SIZE_MAX / sizeof(**strings)) {
        return -1;
    }

    value = malloc(length + 1U);
    if (value == NULL) {
        return -1;
    }

    if (length > 0U) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(value, start, length);
    }
    value[length] = '\0';

    resized = realloc(*strings, new_count * sizeof(*resized));
    if (resized == NULL) {
        free(value);
        return -1;
    }

    resized[*count] = value;
    *strings = resized;
    *count = new_count;

    return 0;
}

static int extract_quoted_values(const char *input, char ***values,
                                 size_t *value_count)
{
    const char *cursor;
    const char *start;
    char quote;

    if (input == NULL || values == NULL || value_count == NULL) {
        return -1;
    }

    *values = NULL;
    *value_count = 0U;
    cursor = input;

    while (*cursor != '\0') {
        if (*cursor != '"' && *cursor != '\'') {
            ++cursor;
            continue;
        }

        quote = *cursor;
        ++cursor;
        start = cursor;

        while (*cursor != '\0' && *cursor != quote) {
            ++cursor;
        }

        if (*cursor == '\0') {
            free_strings(*values, *value_count);
            *values = NULL;
            *value_count = 0U;
            return -1;
        }

        if (append_string(values, value_count, start, cursor) != 0) {
            free_strings(*values, *value_count);
            *values = NULL;
            *value_count = 0U;
            return -1;
        }

        ++cursor;
    }

    return 0;
}

int main(void)
{
    static const char input[] =
        "name=\"Alice\" city='London' role=\"Developer\"";
    char **values = NULL;
    size_t value_count = 0U;
    size_t i;

    if (extract_quoted_values(input, &values, &value_count) != 0) {
        fputs("Failed to extract quoted values.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < value_count; ++i) {
        if (puts(values[i]) == EOF) {
            free_strings(values, value_count);
            return EXIT_FAILURE;
        }
    }

    free_strings(values, value_count);
    return EXIT_SUCCESS;
}
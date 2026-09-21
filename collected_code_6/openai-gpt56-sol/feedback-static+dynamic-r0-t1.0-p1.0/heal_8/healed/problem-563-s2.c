#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void free_strings(char **strings, size_t count)
{
    if (strings == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(strings[i]);
    }

    free(strings);
}

static int append_value(char ***values, size_t *count, size_t *capacity,
                        const char *start, size_t length)
{
    char *value;

    if (values == NULL || count == NULL || capacity == NULL ||
        start == NULL || *count > *capacity || length == SIZE_MAX) {
        return -1;
    }

    value = malloc(length + 1);
    if (value == NULL) {
        return -1;
    }

    if (length != 0) {
        memcpy(value, start, length);
    }
    value[length] = '\0';

    if (*count == *capacity) {
        size_t new_capacity;
        char **resized;

        if (*capacity == 0) {
            new_capacity = 4;
        } else {
            if (*capacity > SIZE_MAX / 2) {
                free(value);
                return -1;
            }
            new_capacity = *capacity * 2;
        }

        if (new_capacity > SIZE_MAX / sizeof(*resized)) {
            free(value);
            return -1;
        }

        resized = realloc(*values, new_capacity * sizeof(*resized));
        if (resized == NULL) {
            free(value);
            return -1;
        }

        *values = resized;
        *capacity = new_capacity;
    }

    (*values)[*count] = value;
    ++*count;

    return 0;
}

static int extract_quoted_values(const char *input, char ***values,
                                 size_t *count)
{
    char **result = NULL;
    size_t result_count = 0;
    size_t capacity = 0;
    const char *start = NULL;
    int escaped = 0;

    if (input == NULL || values == NULL || count == NULL) {
        return -1;
    }

    *values = NULL;
    *count = 0;

    for (const char *p = input; *p != '\0'; ++p) {
        if (start == NULL) {
            if (*p == '"') {
                start = p + 1;
                escaped = 0;
            }
            continue;
        }

        if (*p == '\\' && !escaped) {
            escaped = 1;
            continue;
        }

        if (*p == '"' && !escaped) {
            size_t length = (size_t)(p - start);

            if (append_value(&result, &result_count, &capacity,
                             start, length) != 0) {
                free_strings(result, result_count);
                return -1;
            }

            start = NULL;
            escaped = 0;
            continue;
        }

        escaped = 0;
    }

    if (start != NULL) {
        free_strings(result, result_count);
        return -1;
    }

    *values = result;
    *count = result_count;
    return 0;
}

int main(void)
{
    static const char input[] =
        "The values are \"first\", \"second\", and \"third\".";
    char **values = NULL;
    size_t count = 0;

    if (extract_quoted_values(input, &values, &count) != 0) {
        fputs("Failed to extract quoted values.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (puts(values[i]) == EOF) {
            free_strings(values, count);
            return EXIT_FAILURE;
        }
    }

    free_strings(values, count);
    return EXIT_SUCCESS;
}
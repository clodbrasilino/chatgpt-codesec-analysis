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

    for (i = 0; i < count; ++i) {
        free(strings[i]);
    }

    free(strings);
}

static int extract_quoted_values(const char *input, char ***values, size_t *count)
{
    const char *cursor;
    char **result = NULL;
    size_t capacity = 0;
    size_t used = 0;

    if (input == NULL || values == NULL || count == NULL) {
        return -1;
    }

    *values = NULL;
    *count = 0;
    cursor = input;

    for (;;) {
        const char *start;
        const char *end;
        char *value;
        size_t length;

        start = strchr(cursor, '"');
        if (start == NULL) {
            break;
        }

        ++start;
        end = strchr(start, '"');
        if (end == NULL) {
            free_strings(result, used);
            return -1;
        }

        length = (size_t)(end - start);
        if (length > SIZE_MAX - 1) {
            free_strings(result, used);
            return -1;
        }

        value = malloc(length + 1);
        if (value == NULL) {
            free_strings(result, used);
            return -1;
        }

        if (length > 0) {
            memcpy(value, start, length);
        }
        value[length] = '\0';

        if (used == capacity) {
            char **resized;
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 4;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(value);
                    free_strings(result, used);
                    return -1;
                }
                new_capacity = capacity * 2;
            }

            if (new_capacity > SIZE_MAX / sizeof(*result)) {
                free(value);
                free_strings(result, used);
                return -1;
            }

            resized = realloc(result, new_capacity * sizeof(*result));
            if (resized == NULL) {
                free(value);
                free_strings(result, used);
                return -1;
            }

            result = resized;
            capacity = new_capacity;
        }

        result[used++] = value;
        cursor = end + 1;
    }

    *values = result;
    *count = used;
    return 0;
}

int main(void)
{
    static const char input[] =
        "Name: \"Alice\", City: \"London\", Role: \"Developer\"";
    char **values = NULL;
    size_t count = 0;
    size_t i;

    if (extract_quoted_values(input, &values, &count) != 0) {
        fputs("Failed to extract quoted values.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        if (puts(values[i]) == EOF) {
            free_strings(values, count);
            return EXIT_FAILURE;
        }
    }

    free_strings(values, count);
    return EXIT_SUCCESS;
}
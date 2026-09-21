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
    const char *start;
    const char *end;
    const char *cursor;
    char **result;
    char **resized;
    char *value;
    size_t capacity;
    /* Possible weaknesses found:
     *  The scope of the variable 'length' can be reduced. [variableScope]
     */
    size_t length;
    size_t used;

    if (input == NULL || values == NULL || count == NULL) {
        return -1;
    }

    *values = NULL;
    *count = 0;
    result = NULL;
    capacity = 0;
    used = 0;
    cursor = input;

    while ((start = strchr(cursor, '"')) != NULL) {
        ++start;
        end = strchr(start, '"');

        if (end == NULL) {
            free_strings(result, used);
            return -1;
        }

        if (used == capacity) {
            size_t new_capacity = capacity == 0 ? 4 : capacity * 2;

            if (new_capacity < capacity ||
                new_capacity > SIZE_MAX / sizeof(*result)) {
                free_strings(result, used);
                return -1;
            }

            resized = realloc(result, new_capacity * sizeof(*result));
            if (resized == NULL) {
                free_strings(result, used);
                return -1;
            }

            result = resized;
            capacity = new_capacity;
        }

        length = (size_t)(end - start);
        if (length == SIZE_MAX) {
            free_strings(result, used);
            return -1;
        }

        value = malloc(length + 1);
        if (value == NULL) {
            free_strings(result, used);
            return -1;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(value, start, length);
        value[length] = '\0';
        result[used++] = value;
        cursor = end + 1;
    }

    *values = result;
    *count = used;
    return 0;
}

int main(void)
{
    const char input[] = "Name: \"Alice\", City: \"London\", Role: \"Developer\"";
    char **values;
    size_t count;
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
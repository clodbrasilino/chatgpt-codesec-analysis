#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *join_strings(const char *const *elements, size_t count, const char *delimiter)
{
    size_t total_length = 0;
    size_t delimiter_length;
    size_t i;
    char *result;
    char *cursor;

    if (elements == NULL || delimiter == NULL || count == 0) {
        return NULL;
    }

    delimiter_length = strlen(delimiter);

    for (i = 0; i < count; i++) {
        size_t element_length;

        if (elements[i] == NULL) {
            return NULL;
        }

        element_length = strlen(elements[i]);

        if (element_length > SIZE_MAX - total_length) {
            return NULL;
        }
        total_length += element_length;

        if (i + 1 < count) {
            if (delimiter_length > SIZE_MAX - total_length) {
                return NULL;
            }
            total_length += delimiter_length;
        }
    }

    result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    cursor = result;
    for (i = 0; i < count; i++) {
        size_t element_length = strlen(elements[i]);

        memcpy(cursor, elements[i], element_length);
        cursor += element_length;

        if (i + 1 < count) {
            memcpy(cursor, delimiter, delimiter_length);
            cursor += delimiter_length;
        }
    }
    *cursor = '\0';

    return result;
}

int main(void)
{
    const char *tuple[] = {"apple", "banana", "cherry", "date"};
    size_t count = sizeof(tuple) / sizeof(tuple[0]);
    const char *delimiter = ", ";
    char *joined = join_strings(tuple, count, delimiter);

    if (joined == NULL) {
        fprintf(stderr, "Error: failed to join strings\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", joined);

    free(joined);
    joined = NULL;

    return EXIT_SUCCESS;
}
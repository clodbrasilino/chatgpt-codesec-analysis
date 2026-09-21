#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define JOIN_MAX_STRING_LENGTH 4096U

char *join_strings(const char *const *elements, size_t count, const char *delimiter)
{
    size_t total_length = 0;
    size_t delimiter_length;
    size_t i;
    char *result;
    char *cursor;
    size_t buffer_size;
    size_t remaining;

    if (elements == NULL || delimiter == NULL || count == 0) {
        return NULL;
    }

    delimiter_length = strnlen(delimiter, JOIN_MAX_STRING_LENGTH + 1);
    if (delimiter_length > JOIN_MAX_STRING_LENGTH) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        size_t element_length;

        if (elements[i] == NULL) {
            return NULL;
        }

        element_length = strnlen(elements[i], JOIN_MAX_STRING_LENGTH + 1);
        if (element_length > JOIN_MAX_STRING_LENGTH) {
            return NULL;
        }

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

    if (total_length == SIZE_MAX) {
        return NULL;
    }

    buffer_size = total_length + 1;

    result = malloc(buffer_size);
    if (result == NULL) {
        return NULL;
    }

    cursor = result;
    remaining = buffer_size;

    for (i = 0; i < count; i++) {
        size_t element_length = strnlen(elements[i], JOIN_MAX_STRING_LENGTH + 1);

        if (element_length > JOIN_MAX_STRING_LENGTH || element_length >= remaining) {
            free(result);
            return NULL;
        }

        memcpy(cursor, elements[i], element_length);
        cursor += element_length;
        remaining -= element_length;

        if (i + 1 < count) {
            if (delimiter_length >= remaining) {
                free(result);
                return NULL;
            }

            memcpy(cursor, delimiter, delimiter_length);
            cursor += delimiter_length;
            remaining -= delimiter_length;
        }
    }

    if (remaining < 1) {
        free(result);
        return NULL;
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
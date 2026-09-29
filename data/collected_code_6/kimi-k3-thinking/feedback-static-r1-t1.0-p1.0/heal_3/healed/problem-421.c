#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define JOIN_MAX_STRING_LENGTH ((size_t)16 * 1024 * 1024)

char *join_strings(const char *const *elements, size_t count, const char *delimiter)
{
    size_t total_length = 0;
    size_t delimiter_length;
    size_t i;
    size_t *element_lengths;
    char *result;
    char *cursor;
    size_t remaining;

    if (elements == NULL || delimiter == NULL || count == 0) {
        return NULL;
    }

    delimiter_length = strnlen(delimiter, JOIN_MAX_STRING_LENGTH + 1);
    if (delimiter_length > JOIN_MAX_STRING_LENGTH) {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(*element_lengths)) {
        return NULL;
    }

    element_lengths = malloc(count * sizeof(*element_lengths));
    if (element_lengths == NULL) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        if (elements[i] == NULL) {
            free(element_lengths);
            return NULL;
        }

        element_lengths[i] = strnlen(elements[i], JOIN_MAX_STRING_LENGTH + 1);
        if (element_lengths[i] > JOIN_MAX_STRING_LENGTH) {
            free(element_lengths);
            return NULL;
        }

        if (element_lengths[i] > SIZE_MAX - total_length) {
            free(element_lengths);
            return NULL;
        }
        total_length += element_lengths[i];

        if (i + 1 < count) {
            if (delimiter_length > SIZE_MAX - total_length) {
                free(element_lengths);
                return NULL;
            }
            total_length += delimiter_length;
        }
    }

    if (total_length >= SIZE_MAX) {
        free(element_lengths);
        return NULL;
    }

    result = malloc(total_length + 1);
    if (result == NULL) {
        free(element_lengths);
        return NULL;
    }

    cursor = result;
    remaining = total_length;

    for (i = 0; i < count; i++) {
        if (element_lengths[i] > remaining) {
            free(element_lengths);
            free(result);
            return NULL;
        }
        memcpy(cursor, elements[i], element_lengths[i]);
        cursor += element_lengths[i];
        remaining -= element_lengths[i];

        if (i + 1 < count) {
            if (delimiter_length > remaining) {
                free(element_lengths);
                free(result);
                return NULL;
            }
            memcpy(cursor, delimiter, delimiter_length);
            cursor += delimiter_length;
            remaining -= delimiter_length;
        }
    }

    *cursor = '\0';
    free(element_lengths);

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
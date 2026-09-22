#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define JOIN_MAX_STRING_LENGTH 4096U

static bool copy_into(char *destination, size_t destination_capacity, const char *source, size_t source_length)
{
    if (destination == NULL || source == NULL) {
        return false;
    }

    if (source_length > destination_capacity) {
        return false;
    }

    if (source_length > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(destination, source, source_length);
    }

    return true;
}

char *join_strings(const char *const *elements, size_t count, const char *delimiter)
{
    size_t total_length = 0;
    size_t delimiter_length;
    size_t i;
    char *result;
    char *cursor;
    size_t buffer_size;
    size_t remaining;
    size_t *lengths;

    if (elements == NULL || delimiter == NULL || count == 0) {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(*lengths)) {
        return NULL;
    }

    lengths = malloc(count * sizeof(*lengths));
    if (lengths == NULL) {
        return NULL;
    }

    delimiter_length = strnlen(delimiter, JOIN_MAX_STRING_LENGTH + 1);
    if (delimiter_length > JOIN_MAX_STRING_LENGTH) {
        free(lengths);
        return NULL;
    }

    for (i = 0; i < count; i++) {
        size_t element_length;

        if (elements[i] == NULL) {
            free(lengths);
            return NULL;
        }

        element_length = strnlen(elements[i], JOIN_MAX_STRING_LENGTH + 1);
        if (element_length > JOIN_MAX_STRING_LENGTH) {
            free(lengths);
            return NULL;
        }

        lengths[i] = element_length;

        if (element_length > SIZE_MAX - total_length) {
            free(lengths);
            return NULL;
        }
        total_length += element_length;

        if (i + 1 < count) {
            if (delimiter_length > SIZE_MAX - total_length) {
                free(lengths);
                return NULL;
            }
            total_length += delimiter_length;
        }
    }

    if (total_length == SIZE_MAX) {
        free(lengths);
        return NULL;
    }

    buffer_size = total_length + 1;

    result = malloc(buffer_size);
    if (result == NULL) {
        free(lengths);
        return NULL;
    }

    cursor = result;
    remaining = buffer_size;

    for (i = 0; i < count; i++) {
        size_t element_length = lengths[i];

        if (remaining < 1 ||
            !copy_into(cursor, remaining - 1, elements[i], element_length)) {
            free(result);
            free(lengths);
            return NULL;
        }
        cursor += element_length;
        remaining -= element_length;

        if (i + 1 < count) {
            if (remaining < 1 ||
                !copy_into(cursor, remaining - 1, delimiter, delimiter_length)) {
                free(result);
                free(lengths);
                return NULL;
            }
            cursor += delimiter_length;
            remaining -= delimiter_length;
        }
    }

    free(lengths);

    if (remaining < 1 || cursor != result + total_length) {
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
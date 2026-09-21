#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define JOIN_MAX_STRING_LENGTH ((size_t)1024 * 1024)

static size_t bounded_strlen(const char *s, size_t limit)
{
    size_t length = 0;

    while (length < limit && s[length] != '\0') {
        length++;
    }

    return length;
}

char *join_tuple(const char *const *tuple, size_t size, const char *delimiter)
{
    size_t delimiter_length;
    size_t total_length;
    size_t remaining;
    size_t i;
    char *result;
    char *cursor;

    if (tuple == NULL || delimiter == NULL) {
        return NULL;
    }

    if (size == 0) {
        result = malloc(1);
        if (result == NULL) {
            return NULL;
        }
        result[0] = '\0';
        return result;
    }

    delimiter_length = bounded_strlen(delimiter, JOIN_MAX_STRING_LENGTH + 1);
    if (delimiter_length > JOIN_MAX_STRING_LENGTH) {
        return NULL;
    }

    total_length = 0;

    for (i = 0; i < size; i++) {
        size_t element_length;

        if (tuple[i] == NULL) {
            return NULL;
        }

        element_length = bounded_strlen(tuple[i], JOIN_MAX_STRING_LENGTH + 1);
        if (element_length > JOIN_MAX_STRING_LENGTH) {
            return NULL;
        }

        if (total_length > SIZE_MAX - element_length) {
            return NULL;
        }
        total_length += element_length;

        if (i + 1 < size) {
            if (total_length > SIZE_MAX - delimiter_length) {
                return NULL;
            }
            total_length += delimiter_length;
        }
    }

    if (total_length == SIZE_MAX) {
        return NULL;
    }

    result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    cursor = result;
    remaining = total_length;

    for (i = 0; i < size; i++) {
        size_t element_length;

        element_length = bounded_strlen(tuple[i], JOIN_MAX_STRING_LENGTH + 1);
        if (element_length > JOIN_MAX_STRING_LENGTH) {
            free(result);
            return NULL;
        }

        if (element_length > remaining) {
            free(result);
            return NULL;
        }

        if (element_length > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(cursor, tuple[i], element_length);
            cursor += element_length;
            remaining -= element_length;
        }

        if (i + 1 < size) {
            if (delimiter_length > remaining) {
                free(result);
                return NULL;
            }

            if (delimiter_length > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(cursor, delimiter, delimiter_length);
                cursor += delimiter_length;
                remaining -= delimiter_length;
            }
        }
    }

    if (remaining != 0) {
        free(result);
        return NULL;
    }

    *cursor = '\0';

    return result;
}

int main(void)
{
    const char *tuple[] = {"one", "two", "three", "four"};
    size_t size = sizeof(tuple) / sizeof(tuple[0]);
    const char *delimiter = "-";
    char *joined;

    joined = join_tuple(tuple, size, delimiter);
    if (joined == NULL) {
        fprintf(stderr, "Failed to concatenate tuple elements\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", joined);
    free(joined);
    joined = NULL;

    return EXIT_SUCCESS;
}
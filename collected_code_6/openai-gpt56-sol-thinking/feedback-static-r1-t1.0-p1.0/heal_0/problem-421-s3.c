#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    CONCAT_SUCCESS = 0,
    CONCAT_INVALID_ARGUMENT,
    CONCAT_SIZE_OVERFLOW,
    CONCAT_ALLOCATION_FAILURE
} ConcatStatus;

ConcatStatus concatenate_tuple(
    const char *const elements[],
    size_t count,
    const char *delimiter,
    char **output
) {
    size_t delimiter_length;
    size_t total_length = 0;
    size_t position = 0;
    char *result;

    if (output == NULL) {
        return CONCAT_INVALID_ARGUMENT;
    }

    *output = NULL;

    if (delimiter == NULL || (count > 0 && elements == NULL)) {
        return CONCAT_INVALID_ARGUMENT;
    }

    delimiter_length = strlen(delimiter);

    for (size_t i = 0; i < count; ++i) {
        size_t element_length;

        if (elements[i] == NULL) {
            return CONCAT_INVALID_ARGUMENT;
        }

        element_length = strlen(elements[i]);

        if (element_length > SIZE_MAX - total_length) {
            return CONCAT_SIZE_OVERFLOW;
        }

        total_length += element_length;

        if (i + 1 < count) {
            if (delimiter_length > SIZE_MAX - total_length) {
                return CONCAT_SIZE_OVERFLOW;
            }

            total_length += delimiter_length;
        }
    }

    if (total_length == SIZE_MAX) {
        return CONCAT_SIZE_OVERFLOW;
    }

    result = malloc(total_length + 1);
    if (result == NULL) {
        return CONCAT_ALLOCATION_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        size_t element_length = strlen(elements[i]);

        memcpy(result + position, elements[i], element_length);
        position += element_length;

        if (i + 1 < count) {
            memcpy(result + position, delimiter, delimiter_length);
            position += delimiter_length;
        }
    }

    result[position] = '\0';
    *output = result;

    return CONCAT_SUCCESS;
}

int main(void) {
    const char *tuple[] = {"apple", "banana", "cherry"};
    const size_t tuple_size = sizeof(tuple) / sizeof(tuple[0]);
    char *joined = NULL;
    ConcatStatus status = concatenate_tuple(tuple, tuple_size, ", ", &joined);

    if (status != CONCAT_SUCCESS) {
        if (fputs("Failed to concatenate tuple.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (puts(joined) == EOF) {
        free(joined);
        return EXIT_FAILURE;
    }

    free(joined);
    return EXIT_SUCCESS;
}
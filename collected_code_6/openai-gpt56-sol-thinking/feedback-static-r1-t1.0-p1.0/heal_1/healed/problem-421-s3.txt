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

typedef struct {
    const char *data;
    size_t length;
} StringView;

ConcatStatus concatenate_tuple(
    const StringView elements[],
    size_t count,
    StringView delimiter,
    char **output
) {
    size_t total_length = 0;
    size_t position = 0;
    char *result;

    if (output == NULL) {
        return CONCAT_INVALID_ARGUMENT;
    }

    *output = NULL;

    if ((count > 0 && elements == NULL) ||
        (delimiter.length > 0 && delimiter.data == NULL)) {
        return CONCAT_INVALID_ARGUMENT;
    }

    for (size_t i = 0; i < count; ++i) {
        if (elements[i].length > 0 && elements[i].data == NULL) {
            return CONCAT_INVALID_ARGUMENT;
        }

        if (elements[i].length > SIZE_MAX - total_length) {
            return CONCAT_SIZE_OVERFLOW;
        }

        total_length += elements[i].length;

        if (i + 1 < count) {
            if (delimiter.length > SIZE_MAX - total_length) {
                return CONCAT_SIZE_OVERFLOW;
            }

            total_length += delimiter.length;
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
        if (elements[i].length > 0) {
            memcpy(result + position, elements[i].data, elements[i].length);
            position += elements[i].length;
        }

        if (i + 1 < count && delimiter.length > 0) {
            memcpy(result + position, delimiter.data, delimiter.length);
            position += delimiter.length;
        }
    }

    result[position] = '\0';
    *output = result;

    return CONCAT_SUCCESS;
}

int main(void) {
    static const char apple[] = "apple";
    static const char banana[] = "banana";
    static const char cherry[] = "cherry";
    static const char separator[] = ", ";

    const StringView tuple[] = {
        {apple, sizeof(apple) - 1},
        {banana, sizeof(banana) - 1},
        {cherry, sizeof(cherry) - 1}
    };
    const StringView delimiter = {
        separator,
        sizeof(separator) - 1
    };
    const size_t tuple_size = sizeof(tuple) / sizeof(tuple[0]);
    char *joined = NULL;
    ConcatStatus status;

    status = concatenate_tuple(tuple, tuple_size, delimiter, &joined);
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
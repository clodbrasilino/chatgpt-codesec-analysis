#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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

static ConcatStatus append_bytes(
    char *destination,
    size_t capacity,
    size_t *position,
    const char *source,
    size_t length
) {
    if (destination == NULL || position == NULL) {
        return CONCAT_INVALID_ARGUMENT;
    }

    if (length > 0 && source == NULL) {
        return CONCAT_INVALID_ARGUMENT;
    }

    if (*position > capacity || length > capacity - *position) {
        return CONCAT_SIZE_OVERFLOW;
    }

    for (size_t i = 0; i < length; ++i) {
        destination[*position + i] = source[i];
    }

    *position += length;
    return CONCAT_SUCCESS;
}

ConcatStatus concatenate_tuple(
    const StringView elements[],
    size_t count,
    StringView delimiter,
    char **output
) {
    size_t total_length = 0;
    size_t position = 0;
    char *result;
    /* Possible weaknesses found:
     *  The scope of the variable 'status' can be reduced. [variableScope]
     */
    ConcatStatus status;

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
        status = append_bytes(
            result,
            total_length,
            &position,
            elements[i].data,
            elements[i].length
        );

        if (status != CONCAT_SUCCESS) {
            free(result);
            return status;
        }

        if (i + 1 < count) {
            status = append_bytes(
                result,
                total_length,
                &position,
                delimiter.data,
                delimiter.length
            );

            if (status != CONCAT_SUCCESS) {
                free(result);
                return status;
            }
        }
    }

    if (position != total_length) {
        free(result);
        return CONCAT_SIZE_OVERFLOW;
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

    ConcatStatus status = concatenate_tuple(
        tuple,
        tuple_size,
        delimiter,
        &joined
    );

    if (status != CONCAT_SUCCESS) {
        fputs("Failed to concatenate tuple.\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(joined) == EOF) {
        free(joined);
        return EXIT_FAILURE;
    }

    free(joined);
    return EXIT_SUCCESS;
}
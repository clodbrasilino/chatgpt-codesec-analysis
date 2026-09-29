#include <stddef.h>
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

static int checked_add_size(size_t left, size_t right, size_t *result)
{
    if (result == NULL || right > SIZE_MAX - left) {
        return 0;
    }

    *result = left + right;
    return 1;
}

static int append_bytes(
    char *destination,
    size_t capacity,
    size_t *position,
    const char *source,
    size_t length
)
{
    size_t start;

    if (destination == NULL || position == NULL) {
        return 0;
    }

    if (length == 0) {
        return 1;
    }

    if (source == NULL || *position > capacity ||
        length > capacity - *position) {
        return 0;
    }

    start = *position;

    for (size_t i = 0; i < length; ++i) {
        destination[start + i] = source[i];
    }

    *position = start + length;
    return 1;
}

ConcatStatus concatenate_tuple(
    const StringView elements[],
    size_t count,
    StringView delimiter,
    char **output
)
{
    size_t total_length = 0;
    size_t position = 0;
    char *result;

    if (output == NULL) {
        return CONCAT_INVALID_ARGUMENT;
    }

    *output = NULL;

    if ((count != 0 && elements == NULL) ||
        (delimiter.length != 0 && delimiter.data == NULL)) {
        return CONCAT_INVALID_ARGUMENT;
    }

    for (size_t i = 0; i < count; ++i) {
        if (elements[i].length != 0 && elements[i].data == NULL) {
            return CONCAT_INVALID_ARGUMENT;
        }

        if (!checked_add_size(
                total_length,
                elements[i].length,
                &total_length)) {
            return CONCAT_SIZE_OVERFLOW;
        }

        if (i < count - 1 &&
            !checked_add_size(
                total_length,
                delimiter.length,
                &total_length)) {
            return CONCAT_SIZE_OVERFLOW;
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
        if (!append_bytes(
                result,
                total_length,
                &position,
                elements[i].data,
                elements[i].length)) {
            free(result);
            return CONCAT_SIZE_OVERFLOW;
        }

        if (i < count - 1 &&
            !append_bytes(
                result,
                total_length,
                &position,
                delimiter.data,
                delimiter.length)) {
            free(result);
            return CONCAT_SIZE_OVERFLOW;
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

int main(void)
{
    static const char apple[] = "apple";
    static const char banana[] = "banana";
    static const char cherry[] = "cherry";
    static const char separator[] = ", ";

    const StringView tuple[] = {
        { apple, sizeof(apple) - 1 },
        { banana, sizeof(banana) - 1 },
        { cherry, sizeof(cherry) - 1 }
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
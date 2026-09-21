#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *data;
    size_t length;
} string_view;

static int checked_add_size(size_t *value, size_t increment)
{
    if (increment > SIZE_MAX - *value) {
        return 0;
    }

    *value += increment;
    return 1;
}

static int append_bytes(char *destination, size_t capacity, size_t *position,
                        const char *source, size_t length)
{
    if (*position > capacity || length > capacity - *position) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        destination[*position + i] = source[i];
    }

    *position += length;
    return 1;
}

char *concatenate_tuple(const string_view tuple[], size_t count,
                        string_view delimiter)
{
    const string_view *item;
    size_t remaining;
    size_t content_length = 0;
    size_t position = 0;
    char *result;

    if ((count != 0 && tuple == NULL) ||
        (delimiter.length != 0 && delimiter.data == NULL)) {
        return NULL;
    }

    item = tuple;
    remaining = count;

    while (remaining != 0) {
        if (item->length != 0 && item->data == NULL) {
            return NULL;
        }

        if (!checked_add_size(&content_length, item->length)) {
            return NULL;
        }

        --remaining;

        if (remaining != 0) {
            if (!checked_add_size(&content_length, delimiter.length)) {
                return NULL;
            }
            ++item;
        }
    }

    if (content_length == SIZE_MAX) {
        return NULL;
    }

    result = malloc(content_length + 1);
    if (result == NULL) {
        return NULL;
    }

    item = tuple;
    remaining = count;

    while (remaining != 0) {
        if (!append_bytes(result, content_length, &position,
                          item->data, item->length)) {
            free(result);
            return NULL;
        }

        --remaining;

        if (remaining != 0) {
            if (!append_bytes(result, content_length, &position,
                              delimiter.data, delimiter.length)) {
                free(result);
                return NULL;
            }
            ++item;
        }
    }

    if (position != content_length) {
        free(result);
        return NULL;
    }

    result[position] = '\0';
    return result;
}

int main(void)
{
    const string_view tuple[] = {
        {"apple", sizeof("apple") - 1},
        {"banana", sizeof("banana") - 1},
        {"cherry", sizeof("cherry") - 1}
    };
    const string_view delimiter = {", ", sizeof(", ") - 1};
    const size_t count = sizeof(tuple) / sizeof(tuple[0]);
    char *result = concatenate_tuple(tuple, count, delimiter);
    int status;

    if (result == NULL) {
        return EXIT_FAILURE;
    }

    status = printf("%s\n", result);
    free(result);

    return status < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}
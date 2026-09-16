#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *const *items;
    size_t count;
} StringTuple;

char *concatenate_tuple(StringTuple tuple, const char *delimiter)
{
    size_t delimiter_length;
    size_t total_length = 1;
    char *result;
    char *position;

    if (delimiter == NULL || (tuple.count > 0 && tuple.items == NULL)) {
        errno = EINVAL;
        return NULL;
    }

    delimiter_length = strlen(delimiter);

    for (size_t i = 0; i < tuple.count; ++i) {
        size_t item_length;

        if (tuple.items[i] == NULL) {
            errno = EINVAL;
            return NULL;
        }

        item_length = strlen(tuple.items[i]);

        if (item_length > SIZE_MAX - total_length) {
            errno = EOVERFLOW;
            return NULL;
        }

        total_length += item_length;

        if (i + 1 < tuple.count) {
            if (delimiter_length > SIZE_MAX - total_length) {
                errno = EOVERFLOW;
                return NULL;
            }

            total_length += delimiter_length;
        }
    }

    result = malloc(total_length);
    if (result == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    position = result;

    for (size_t i = 0; i < tuple.count; ++i) {
        size_t item_length = strlen(tuple.items[i]);

        memcpy(position, tuple.items[i], item_length);
        position += item_length;

        if (i + 1 < tuple.count) {
            memcpy(position, delimiter, delimiter_length);
            position += delimiter_length;
        }
    }

    *position = '\0';
    return result;
}

int main(void)
{
    const char *items[] = {"apple", "banana", "cherry"};
    StringTuple tuple = {items, sizeof(items) / sizeof(items[0])};
    char *result = concatenate_tuple(tuple, ", ");

    if (result == NULL) {
        perror("concatenate_tuple");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *data;
    size_t length;
} StringView;

typedef struct {
    const StringView *items;
    size_t count;
} StringTuple;

char *concatenate_tuple(StringTuple tuple, StringView delimiter)
{
    size_t total_length = 1;
    size_t position = 0;
    char *result;

    if ((tuple.count != 0 && tuple.items == NULL) ||
        (delimiter.length != 0 && delimiter.data == NULL)) {
        errno = EINVAL;
        return NULL;
    }

    for (size_t i = 0; i < tuple.count; ++i) {
        if (tuple.items[i].length != 0 && tuple.items[i].data == NULL) {
            errno = EINVAL;
            return NULL;
        }

        if (tuple.items[i].length > SIZE_MAX - total_length) {
            errno = EOVERFLOW;
            return NULL;
        }

        total_length += tuple.items[i].length;

        if (i + 1 < tuple.count) {
            if (delimiter.length > SIZE_MAX - total_length) {
                errno = EOVERFLOW;
                return NULL;
            }

            total_length += delimiter.length;
        }
    }

    result = malloc(total_length);
    if (result == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    for (size_t i = 0; i < tuple.count; ++i) {
        for (size_t j = 0; j < tuple.items[i].length; ++j) {
            result[position++] = tuple.items[i].data[j];
        }

        if (i + 1 < tuple.count) {
            for (size_t j = 0; j < delimiter.length; ++j) {
                result[position++] = delimiter.data[j];
            }
        }
    }

    result[position] = '\0';
    return result;
}

int main(void)
{
    static const char apple[] = "apple";
    static const char banana[] = "banana";
    static const char cherry[] = "cherry";
    static const char separator[] = ", ";

    const StringView items[] = {
        {apple, sizeof(apple) - 1},
        {banana, sizeof(banana) - 1},
        {cherry, sizeof(cherry) - 1}
    };
    const StringTuple tuple = {
        items,
        sizeof(items) / sizeof(items[0])
    };
    const StringView delimiter = {
        separator,
        sizeof(separator) - 1
    };
    char *result = concatenate_tuple(tuple, delimiter);

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
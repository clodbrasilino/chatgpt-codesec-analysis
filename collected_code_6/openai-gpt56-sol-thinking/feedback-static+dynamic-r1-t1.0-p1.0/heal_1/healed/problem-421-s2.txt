#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *data;
    size_t length;
} StringView;

char *concatenate_tuple(const StringView tuple[], size_t count,
                        StringView delimiter)
{
    size_t total = 1;
    size_t position = 0;
    char *result;

    if (delimiter.data == NULL || (count > 0 && tuple == NULL)) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        if (tuple[i].data == NULL) {
            return NULL;
        }

        if (tuple[i].length > SIZE_MAX - total) {
            return NULL;
        }
        total += tuple[i].length;

        if (i != count - 1) {
            if (delimiter.length > SIZE_MAX - total) {
                return NULL;
            }
            total += delimiter.length;
        }
    }

    result = malloc(total);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        for (size_t j = 0; j < tuple[i].length; ++j) {
            result[position++] = tuple[i].data[j];
        }

        if (i != count - 1) {
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
    const StringView tuple[] = {
        {"apple", sizeof("apple") - 1},
        {"banana", sizeof("banana") - 1},
        {"cherry", sizeof("cherry") - 1}
    };
    const StringView delimiter = {", ", sizeof(", ") - 1};
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
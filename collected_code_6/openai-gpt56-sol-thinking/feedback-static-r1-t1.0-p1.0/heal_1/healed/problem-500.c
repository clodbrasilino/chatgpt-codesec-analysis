#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *data;
    size_t length;
} StringElement;

char *concatenate(const StringElement elements[], size_t count)
{
    size_t total_length = 0;

    if (elements == NULL && count != 0) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        if (elements[i].data == NULL) {
            return NULL;
        }

        if (elements[i].length > SIZE_MAX - total_length) {
            return NULL;
        }

        total_length += elements[i].length;
    }

    if (total_length == SIZE_MAX) {
        return NULL;
    }

    char *result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t offset = 0;

    for (size_t i = 0; i < count; ++i) {
        for (size_t j = 0; j < elements[i].length; ++j) {
            result[offset++] = elements[i].data[j];
        }
    }

    result[offset] = '\0';
    return result;
}

int main(void)
{
    static const StringElement elements[] = {
        {"Hello", sizeof("Hello") - 1},
        {", ", sizeof(", ") - 1},
        {"world", sizeof("world") - 1},
        {"!", sizeof("!") - 1}
    };

    const size_t count = sizeof(elements) / sizeof(elements[0]);
    char *result = concatenate(elements, count);

    if (result == NULL) {
        fputs("Failed to concatenate elements.\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}
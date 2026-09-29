#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    const char *data;
    size_t length;
} StringView;

char *concatenate(const StringView elements[], size_t count)
{
    size_t content_size = 0;
    size_t offset = 0;

    if (count != 0 && elements == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        if (elements[i].length != 0 && elements[i].data == NULL) {
            return NULL;
        }

        if (elements[i].length > SIZE_MAX - content_size - 1) {
            return NULL;
        }

        content_size += elements[i].length;
    }

    char *result = malloc(content_size + 1);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        const size_t length = elements[i].length;

        if (length > content_size - offset) {
            free(result);
            return NULL;
        }

        for (size_t j = 0; j < length; ++j) {
            result[offset + j] = elements[i].data[j];
        }

        offset += length;
    }

    result[offset] = '\0';
    return result;
}

int main(void)
{
    const StringView elements[] = {
        {"Hello", sizeof("Hello") - 1},
        {", ", sizeof(", ") - 1},
        {"world", sizeof("world") - 1},
        {"!", sizeof("!") - 1}
    };
    const size_t count = sizeof(elements) / sizeof(elements[0]);

    char *result = concatenate(elements, count);
    if (result == NULL) {
        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}
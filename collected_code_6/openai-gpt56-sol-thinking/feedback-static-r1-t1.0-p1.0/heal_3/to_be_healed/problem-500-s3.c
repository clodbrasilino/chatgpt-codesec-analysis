#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    const char *data;
    size_t length;
} StringView;

char *concatenate(const StringView elements[], size_t count)
{
    size_t content_size = 0;
    size_t offset = 0;
    char *result;

    if (count != 0 && elements == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        if (elements[i].length != 0 && elements[i].data == NULL) {
            return NULL;
        }

        if (elements[i].length > SIZE_MAX - content_size) {
            return NULL;
        }

        content_size += elements[i].length;
    }

    if (content_size == SIZE_MAX) {
        return NULL;
    }

    result = malloc(content_size + 1);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        size_t length = elements[i].length;

        if (length > content_size - offset) {
            free(result);
            return NULL;
        }

        if (length != 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + offset, elements[i].data, length);
            offset += length;
        }
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
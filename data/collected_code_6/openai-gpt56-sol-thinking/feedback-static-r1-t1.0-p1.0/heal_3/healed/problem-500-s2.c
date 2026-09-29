#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *data;
    size_t length;
} string_view;

char *concatenate_elements(const string_view elements[], size_t count)
{
    size_t total_length = 0;
    size_t offset = 0;

    if (count > 0 && elements == NULL) {
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

    char *result = malloc(total_length + 1U);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        const size_t length = elements[i].length;

        if (offset > total_length || length > total_length - offset) {
            free(result);
            return NULL;
        }

        for (size_t j = 0; j < length; ++j) {
            result[offset + j] = elements[i].data[j];
        }

        offset += length;
    }

    if (offset != total_length) {
        free(result);
        return NULL;
    }

    result[offset] = '\0';
    return result;
}

int main(void)
{
    const string_view elements[] = {
        {"Hello", sizeof("Hello") - 1U},
        {", ", sizeof(", ") - 1U},
        {"world", sizeof("world") - 1U},
        {"!", sizeof("!") - 1U}
    };

    const size_t count = sizeof(elements) / sizeof(elements[0]);
    char *result = concatenate_elements(elements, count);

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
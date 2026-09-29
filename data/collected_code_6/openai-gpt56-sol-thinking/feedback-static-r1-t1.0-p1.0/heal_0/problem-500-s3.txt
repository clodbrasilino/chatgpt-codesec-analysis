#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *concatenate(const char *const elements[], size_t count)
{
    size_t total_size = 1;
    size_t offset = 0;
    char *result;

    if (count > 0 && elements == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        size_t length;

        if (elements[i] == NULL) {
            return NULL;
        }

        length = strlen(elements[i]);

        if (length > SIZE_MAX - total_size) {
            return NULL;
        }

        total_size += length;
    }

    result = malloc(total_size);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        size_t length = strlen(elements[i]);

        memcpy(result + offset, elements[i], length);
        offset += length;
    }

    result[offset] = '\0';
    return result;
}

int main(void)
{
    const char *elements[] = {"Hello", ", ", "world", "!"};
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
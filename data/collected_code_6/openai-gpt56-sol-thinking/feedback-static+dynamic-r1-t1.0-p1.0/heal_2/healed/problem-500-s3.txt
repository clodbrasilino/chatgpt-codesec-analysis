#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

char *concatenate(const char *const elements[],
                  const size_t lengths[],
                  size_t count)
{
    size_t total_size = 1;
    size_t offset = 0;

    if (count > 0 && (elements == NULL || lengths == NULL)) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        if (elements[i] == NULL) {
            return NULL;
        }

        if (lengths[i] > SIZE_MAX - total_size) {
            return NULL;
        }

        total_size += lengths[i];
    }

    char *result = malloc(total_size);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        if (offset > total_size - 1 ||
            lengths[i] > total_size - 1 - offset) {
            free(result);
            return NULL;
        }

        for (size_t j = 0; j < lengths[i]; ++j) {
            result[offset++] = elements[i][j];
        }
    }

    result[offset] = '\0';
    return result;
}

int main(void)
{
    static const char element0[] = "Hello";
    static const char element1[] = ", ";
    static const char element2[] = "world";
    static const char element3[] = "!";

    const char *elements[] = {
        element0,
        element1,
        element2,
        element3
    };

    const size_t lengths[] = {
        sizeof(element0) - 1,
        sizeof(element1) - 1,
        sizeof(element2) - 1,
        sizeof(element3) - 1
    };

    const size_t count = sizeof(elements) / sizeof(elements[0]);
    char *result = concatenate(elements, lengths, count);

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
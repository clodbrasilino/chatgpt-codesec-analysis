#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *concatenate_elements(const char *const elements[], size_t count)
{
    size_t *lengths = NULL;
    size_t total_length = 0;
    size_t offset = 0;
    char *result;

    if (count > 0 && elements == NULL) {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(*lengths)) {
        return NULL;
    }

    if (count > 0) {
        lengths = malloc(count * sizeof(*lengths));
        if (lengths == NULL) {
            return NULL;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        size_t length = 0;

        if (elements[i] == NULL) {
            free(lengths);
            return NULL;
        }

        while (elements[i][length] != '\0') {
            if (length == SIZE_MAX - 1U) {
                free(lengths);
                return NULL;
            }
            ++length;
        }

        if (length > SIZE_MAX - total_length - 1U) {
            free(lengths);
            return NULL;
        }

        lengths[i] = length;
        total_length += length;
    }

    result = malloc(total_length + 1U);
    if (result == NULL) {
        free(lengths);
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        for (size_t j = 0; j < lengths[i]; ++j) {
            result[offset++] = elements[i][j];
        }
    }

    result[offset] = '\0';
    free(lengths);
    return result;
}

int main(void)
{
    const char *elements[] = {"Hello", ", ", "world", "!"};
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
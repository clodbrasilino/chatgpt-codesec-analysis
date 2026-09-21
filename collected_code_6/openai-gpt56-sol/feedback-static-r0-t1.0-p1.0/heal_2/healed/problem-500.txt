#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concatenate(const char *const elements[], const size_t lengths[], size_t count)
{
    if (count != 0 && (elements == NULL || lengths == NULL)) {
        return NULL;
    }

    size_t total_length = 0;

    for (size_t i = 0; i < count; ++i) {
        if (elements[i] == NULL) {
            return NULL;
        }

        if (lengths[i] > SIZE_MAX - total_length - 1) {
            return NULL;
        }

        total_length += lengths[i];
    }

    char *result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t offset = 0;

    for (size_t i = 0; i < count; ++i) {
        size_t remaining = total_length - offset;

        if (lengths[i] > remaining) {
            free(result);
            return NULL;
        }

        if (lengths[i] != 0) {
            memcpy(result + offset, elements[i], lengths[i]);
        }

        offset += lengths[i];
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

    const char *const elements[] = {
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
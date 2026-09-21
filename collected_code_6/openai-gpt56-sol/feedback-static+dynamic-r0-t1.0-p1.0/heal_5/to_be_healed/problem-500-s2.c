#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *concatenate(const char *const elements[],
                  const size_t lengths[],
                  size_t count)
{
    if (count > 0 && (elements == NULL || lengths == NULL)) {
        return NULL;
    }

    size_t total_length = 0;

    for (size_t i = 0; i < count; ++i) {
        if (elements[i] == NULL) {
            return NULL;
        }

        if (lengths[i] > SIZE_MAX - total_length) {
            return NULL;
        }

        total_length += lengths[i];
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
        const size_t length = lengths[i];

        if (offset > total_length || length > total_length - offset) {
            free(result);
            return NULL;
        }

        if (length != 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + offset, elements[i], length);
            offset += length;
        }
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

    puts(result);
    free(result);

    return EXIT_SUCCESS;
}
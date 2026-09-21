#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *concatenate(const char *const elements[], size_t count)
{
    if (count != 0 && elements == NULL) {
        return NULL;
    }

    size_t total_length = 0;
    size_t *lengths = NULL;

    if (count != 0) {
        if (count > SIZE_MAX / sizeof(*lengths)) {
            return NULL;
        }

        lengths = malloc(count * sizeof(*lengths));
        if (lengths == NULL) {
            return NULL;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (elements[i] == NULL) {
            free(lengths);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        lengths[i] = strlen(elements[i]);

        if (lengths[i] > SIZE_MAX - total_length - 1) {
            free(lengths);
            return NULL;
        }

        total_length += lengths[i];
    }

    char *result = malloc(total_length + 1);
    if (result == NULL) {
        free(lengths);
        return NULL;
    }

    size_t offset = 0;

    for (size_t i = 0; i < count; ++i) {
        if (lengths[i] > total_length - offset) {
            free(result);
            free(lengths);
            return NULL;
        }

        if (lengths[i] != 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + offset, elements[i], lengths[i]);
            offset += lengths[i];
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
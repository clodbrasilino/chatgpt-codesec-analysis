#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *concatenate(const char *const elements[], size_t count)
{
    size_t total_length = 0;
    size_t *lengths = NULL;
    char *result = NULL;
    char *destination = NULL;

    if (count != 0 && elements == NULL) {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(*lengths)) {
        return NULL;
    }

    if (count != 0) {
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

    result = malloc(total_length + 1);
    if (result == NULL) {
        free(lengths);
        return NULL;
    }

    destination = result;

    for (size_t i = 0; i < count; ++i) {
        if (lengths[i] != 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(destination, elements[i], lengths[i]);
            destination += lengths[i];
        }
    }

    *destination = '\0';
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
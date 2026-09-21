#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *concatenate(const char *const elements[], size_t count)
{
    size_t total_length = 0;
    char *result;
    char *destination;

    if (count != 0 && elements == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        size_t length;

        if (elements[i] == NULL) {
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        length = strlen(elements[i]);

        if (length > SIZE_MAX - total_length - 1) {
            return NULL;
        }

        total_length += length;
    }

    result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    destination = result;

    for (size_t i = 0; i < count; ++i) {
        size_t remaining = total_length - (size_t)(destination - result);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t length = strlen(elements[i]);

        if (length > remaining) {
            free(result);
            return NULL;
        }

        if (length != 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(destination, elements[i], length);
            destination += length;
        }
    }

    *destination = '\0';
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
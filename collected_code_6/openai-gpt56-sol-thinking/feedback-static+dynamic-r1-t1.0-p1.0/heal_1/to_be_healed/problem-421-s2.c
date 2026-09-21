#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concatenate_tuple(const char *const tuple[], size_t count,
                        const char *delimiter)
{
    size_t total = 1;
    size_t delimiter_length;
    char *result;
    char *position;

    if (delimiter == NULL || (count > 0 && tuple == NULL)) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    delimiter_length = strlen(delimiter);

    for (size_t i = 0; i < count; ++i) {
        size_t element_length;

        if (tuple[i] == NULL) {
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        element_length = strlen(tuple[i]);

        if (element_length > SIZE_MAX - total) {
            return NULL;
        }
        total += element_length;

        if (i + 1 < count) {
            if (delimiter_length > SIZE_MAX - total) {
                return NULL;
            }
            total += delimiter_length;
        }
    }

    result = malloc(total);
    if (result == NULL) {
        return NULL;
    }

    position = result;

    for (size_t i = 0; i < count; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t element_length = strlen(tuple[i]);

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(position, tuple[i], element_length);
        position += element_length;

        if (i + 1 < count) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(position, delimiter, delimiter_length);
            position += delimiter_length;
        }
    }

    *position = '\0';
    return result;
}

int main(void)
{
    const char *tuple[] = {"apple", "banana", "cherry"};
    size_t count = sizeof(tuple) / sizeof(tuple[0]);
    char *result = concatenate_tuple(tuple, count, ", ");
    int status;

    if (result == NULL) {
        return EXIT_FAILURE;
    }

    status = printf("%s\n", result);
    free(result);

    return status < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_tuple(const char* tuple[], size_t size, const char* delimiter) {
    if (tuple == NULL || delimiter == NULL || size == 0) {
        return NULL;
    }

    size_t total_length = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t delimiter_length = strlen(delimiter);

    for (size_t i = 0; i < size; i++) {
        if (tuple[i] == NULL) {
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        total_length += strlen(tuple[i]);
        if (i < size - 1) {
            total_length += delimiter_length;
        }
    }

    char* result = (char*)malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t current_pos = 0;

    for (size_t i = 0; i < size; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t str_len = strlen(tuple[i]);
        if (str_len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + current_pos, tuple[i], str_len);
            current_pos += str_len;
        }

        if (i < size - 1) {
            if (delimiter_length > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + current_pos, delimiter, delimiter_length);
                current_pos += delimiter_length;
            }
        }
    }

    result[current_pos] = '\0';

    return result;
}

int main(void) {
    const char* tuple[] = {"apple", "banana", "cherry"};
    size_t size = sizeof(tuple) / sizeof(tuple[0]);
    const char* delimiter = ", ";

    char* result = concatenate_tuple(tuple, size, delimiter);
    if (result == NULL) {
        return EXIT_FAILURE;
    }

    printf("%s\n", result);

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}
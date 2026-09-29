#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *join_tuple(const char *const *tuple, size_t size, const char *delimiter)
{
    size_t delimiter_length;
    size_t total_length;
    size_t i;
    char *result;
    char *cursor;

    if (tuple == NULL || delimiter == NULL) {
        return NULL;
    }

    if (size == 0) {
        result = malloc(1);
        if (result == NULL) {
            return NULL;
        }
        result[0] = '\0';
        return result;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    delimiter_length = strlen(delimiter);
    total_length = 0;

    for (i = 0; i < size; i++) {
        size_t element_length;

        if (tuple[i] == NULL) {
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        element_length = strlen(tuple[i]);
        if (total_length > SIZE_MAX - element_length) {
            return NULL;
        }
        total_length += element_length;

        if (i + 1 < size) {
            if (total_length > SIZE_MAX - delimiter_length) {
                return NULL;
            }
            total_length += delimiter_length;
        }
    }

    if (total_length == SIZE_MAX) {
        return NULL;
    }

    result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    cursor = result;
    for (i = 0; i < size; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t element_length = strlen(tuple[i]);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(cursor, tuple[i], element_length);
        cursor += element_length;

        if (i + 1 < size) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(cursor, delimiter, delimiter_length);
            cursor += delimiter_length;
        }
    }
    *cursor = '\0';

    return result;
}

int main(void)
{
    const char *tuple[] = {"one", "two", "three", "four"};
    size_t size = sizeof(tuple) / sizeof(tuple[0]);
    const char *delimiter = "-";
    char *joined;

    joined = join_tuple(tuple, size, delimiter);
    if (joined == NULL) {
        fprintf(stderr, "Failed to concatenate tuple elements\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", joined);
    free(joined);
    joined = NULL;

    return EXIT_SUCCESS;
}
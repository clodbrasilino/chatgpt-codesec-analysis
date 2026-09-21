#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concatenate_tuple(const char **tuple, size_t count, const char *delimiter) {
    if (tuple == NULL || delimiter == NULL) {
        return NULL;
    }

    if (count == 0) {
        char *result = malloc(1);
        if (result == NULL) {
            return NULL;
        }
        result[0] = '\0';
        return result;
    }

    size_t total_length = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t delimiter_length = strlen(delimiter);

    for (size_t i = 0; i < count; i++) {
        if (tuple[i] != NULL) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            total_length += strlen(tuple[i]);
        }
        if (i < count - 1) {
            total_length += delimiter_length;
        }
    }

    char *result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    char *current = result;

    for (size_t i = 0; i < count; i++) {
        if (tuple[i] != NULL) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(tuple[i]);
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(current, tuple[i], len);
            current += len;
        }
        if (i < count - 1) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(current, delimiter, delimiter_length);
            current += delimiter_length;
        }
    }

    *current = '\0';

    return result;
}

int main(void) {
    const char *tuple[] = {"apple", "banana", "cherry"};
    size_t count = sizeof(tuple) / sizeof(tuple[0]);
    const char *delimiter = ", ";

    char *result = concatenate_tuple(tuple, count, delimiter);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    const char *empty_tuple[] = {NULL};
    char *empty_result = concatenate_tuple(empty_tuple, 0, delimiter);
    if (empty_result != NULL) {
        free(empty_result);
    }

    return 0;
}
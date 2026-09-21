#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_tuple(const char** tuple, size_t tuple_size, const char* delimiter) {
    if (tuple == NULL || delimiter == NULL || tuple_size == 0) {
        return NULL;
    }

    size_t total_length = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t delimiter_length = strlen(delimiter);

    for (size_t i = 0; i < tuple_size; ++i) {
        if (tuple[i] != NULL) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            total_length += strlen(tuple[i]);
        }
    }

    total_length += (tuple_size - 1) * delimiter_length + 1;

    char* result = (char*)malloc(total_length);
    if (result == NULL) {
        return NULL;
    }

    char* current_pos = result;

    for (size_t i = 0; i < tuple_size; ++i) {
        if (tuple[i] != NULL) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(tuple[i]);
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(current_pos, tuple[i], len);
            current_pos += len;
        }
        if (i < tuple_size - 1) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(current_pos, delimiter, delimiter_length);
            current_pos += delimiter_length;
        }
    }

    *current_pos = '\0';

    return result;
}

int main(void) {
    const char* tuple[] = {"apple", "banana", "cherry", "date"};
    size_t tuple_size = sizeof(tuple) / sizeof(tuple[0]);
    const char* delimiter = ", ";

    char* concatenated_string = concatenate_tuple(tuple, tuple_size, delimiter);

    if (concatenated_string != NULL) {
        printf("%s\n", concatenated_string);
        free(concatenated_string);
    } else {
        fprintf(stderr, "Failed to concatenate tuple.\n");
    }

    return 0;
}
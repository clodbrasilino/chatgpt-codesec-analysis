#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* tuple_concat(const char** tuple, size_t size, const char* delimiter) {
    if (tuple == NULL || delimiter == NULL || size == 0) {
        return NULL;
    }

    size_t total_len = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t delim_len = strlen(delimiter);
    
    for (size_t i = 0; i < size; i++) {
        if (tuple[i] == NULL) {
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        total_len += strlen(tuple[i]);
        if (i < size - 1) {
            total_len += delim_len;
        }
    }

    char* result = (char*)malloc(total_len + 1);
    if (result == NULL) {
        return NULL;
    }

    char* ptr = result;
    size_t remaining = total_len + 1;

    for (size_t i = 0; i < size; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t item_len = strlen(tuple[i]);
        size_t bytes_to_copy = item_len < remaining ? item_len : remaining;
        if (bytes_to_copy > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(ptr, tuple[i], bytes_to_copy);
            ptr += bytes_to_copy;
            remaining -= bytes_to_copy;
        }
        
        if (i < size - 1) {
            bytes_to_copy = delim_len < remaining ? delim_len : remaining;
            if (bytes_to_copy > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(ptr, delimiter, bytes_to_copy);
                ptr += bytes_to_copy;
                remaining -= bytes_to_copy;
            }
        }
    }

    *ptr = '\0';

    return result;
}

int main(void) {
    const char* tuple[] = {"C", "is", "a", "powerful", "language"};
    size_t size = sizeof(tuple) / sizeof(tuple[0]);
    const char* delimiter = "-";

    char* concatenated = tuple_concat(tuple, size, delimiter);
    if (concatenated != NULL) {
        printf("%s\n", concatenated);
        free(concatenated);
        concatenated = NULL;
    }

    return 0;
}
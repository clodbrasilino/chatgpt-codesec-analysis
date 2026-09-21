#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *tuple_join(const char **tuple, size_t count, const char *delimiter) {
    if (tuple == NULL || delimiter == NULL || count == 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t delim_len = strlen(delimiter);
    size_t total_len = 0;

    for (size_t i = 0; i < count; i++) {
        if (tuple[i] == NULL) {
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(tuple[i]);
        if (len > SIZE_MAX - total_len) {
            return NULL;
        }
        total_len += len;
        if (i < count - 1) {
            if (delim_len > SIZE_MAX - total_len) {
                return NULL;
            }
            total_len += delim_len;
        }
    }

    if (total_len == SIZE_MAX) {
        return NULL;
    }

    size_t result_size = total_len + 1;
    char *result = malloc(result_size);
    if (result == NULL) {
        return NULL;
    }

    size_t written = 0;
    for (size_t i = 0; i < count; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(tuple[i]);
        if (len > result_size - written - 1) {
            free(result);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + written, tuple[i], len);
        written += len;
        
        if (i < count - 1) {
            if (delim_len > result_size - written - 1) {
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + written, delimiter, delim_len);
            written += delim_len;
        }
    }

    result[written] = '\0';

    return result;
}

int main(void) {
    const char *tuple[] = {"apple", "banana", "cherry", "date"};
    size_t count = sizeof(tuple) / sizeof(tuple[0]);
    const char *delimiter = ", ";

    char *result = tuple_join(tuple, count, delimiter);
    if (result == NULL) {
        fprintf(stderr, "Failed to join tuple\n");
        return 1;
    }

    printf("%s\n", result);

    free(result);

    return 0;
}
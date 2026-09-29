#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concat_tuples(const char *tuple[], size_t n, const char *delimiter) {
    if (n == 0) return NULL;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t delimiter_len = (delimiter != NULL) ? strlen(delimiter) : 0;
    size_t total_len = 1; 
    for (size_t i = 0; i < n; ++i) {
        if (tuple[i] != NULL) {
            total_len += strnlen(tuple[i], 50);
        }
    }
    total_len += (n - 1) * delimiter_len;

    char *result = (char *)malloc(total_len);
    if (result == NULL) return NULL;

    result[0] = '\0';
    size_t current_pos = 0;
    for (size_t i = 0; i < n; ++i) {
        if (tuple[i] != NULL) {
            size_t len = strnlen(tuple[i], 50);
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + current_pos, tuple[i], len);
            current_pos += len;
        }
        if (i < n - 1 && delimiter != NULL) {
            size_t len = strnlen(delimiter, 50);
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + current_pos, delimiter, len);
            current_pos += len;
        }
    }
    result[total_len - 1] = '\0';

    return result;
}

int main() {
    const char *tuple[] = {"apple", "banana", "cherry"};
    size_t n = sizeof(tuple) / sizeof(tuple[0]);
    const char *delimiter = ",";

    char *result = concat_tuples(tuple, n, delimiter);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    return 0;
}
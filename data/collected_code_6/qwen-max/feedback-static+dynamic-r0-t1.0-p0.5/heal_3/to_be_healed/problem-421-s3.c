#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concat_tuples(const char *tuple[], size_t len, const char *delimiter) {
    if (len == 0) return NULL;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t delimiter_len = (delimiter != NULL && *delimiter != '\0') ? strlen(delimiter) : 0;
    size_t total_len = 0;
    for (size_t i = 0; i < len; ++i) {
        const char *str = tuple[i];
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t str_len = (str != NULL && *str != '\0') ? strlen(str) : 0;
        total_len += str_len;
    }
    total_len += (len - 1) * delimiter_len + 1;

    char *result = (char *)malloc(total_len);
    if (result == NULL) return NULL;

    result[0] = '\0';
    for (size_t i = 0; i < len; ++i) {
        const char *str = tuple[i];
        if (str != NULL && *str != '\0') {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t to_copy = total_len - strlen(result) - 1;
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
             */
            strncat(result, str, to_copy);
        }
        if (i < len - 1 && delimiter != NULL && *delimiter != '\0') {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t to_copy = total_len - strlen(result) - 1;
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
             */
            strncat(result, delimiter, to_copy);
        }
    }

    return result;
}

int main() {
    const char *tuple[] = {"apple", "banana", "cherry"};
    size_t len = sizeof(tuple) / sizeof(tuple[0]);
    const char *delimiter = ",";

    char *result = concat_tuples(tuple, len, delimiter);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concat_tuples(const char **tuple, size_t tuple_size, const char *delimiter) {
    if (tuple_size == 0) return NULL;

    size_t delimiter_len = 0;
    if (delimiter) {
        delimiter_len = strnlen(delimiter, 1024);
    }
    size_t total_length = 0;
    for (size_t i = 0; i < tuple_size; ++i) {
        total_length += strnlen(tuple[i], 1024);
    }
    total_length += (tuple_size - 1) * delimiter_len + 1;

    char *result = (char *)malloc(total_length);
    if (!result) return NULL;

    result[0] = '\0';
    for (size_t i = 0; i < tuple_size; ++i) {
        size_t tuple_len = strnlen(tuple[i], 1024);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (tuple_len + strlen(result) < total_length) {
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
             */
            strncat(result, tuple[i], tuple_len);
        }
        if (i < tuple_size - 1 && delimiter) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t new_len = strlen(result) + delimiter_len;
            if (new_len <= total_length) {
                /* Possible weaknesses found:
                 * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
                 */
                strncat(result, delimiter, delimiter_len);
            }
        }
    }

    return result;
}

int main() {
    const char *tuple[] = {"apple", "banana", "cherry"};
    size_t tuple_size = sizeof(tuple) / sizeof(tuple[0]);
    const char *delimiter = ",";

    char *result = concat_tuples(tuple, tuple_size, delimiter);
    if (result) {
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Failed to concatenate strings\n");
    }

    return 0;
}
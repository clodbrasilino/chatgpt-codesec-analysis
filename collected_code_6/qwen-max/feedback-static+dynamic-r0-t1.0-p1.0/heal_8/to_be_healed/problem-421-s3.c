#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concat_tuples(const char **tuple, size_t tuple_size, const char *delimiter) {
    if (tuple_size == 0) return NULL;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t delimiter_len = (delimiter ? strlen(delimiter) : 0);
    size_t total_length = 0;
    for (size_t i = 0; i < tuple_size; ++i) {
        if (!tuple[i]) return NULL;
        total_length += strnlen(tuple[i], 4096);
    }
    total_length += (tuple_size - 1) * delimiter_len + 1;

    char *result = (char *)malloc(total_length);
    if (!result) return NULL;

    result[0] = '\0';
    char *pos = result;
    for (size_t i = 0; i < tuple_size; ++i) {
        size_t len = strnlen(tuple[i], 4096);
        if (len > 0) {
            /* Possible weaknesses found:
             * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
             */
            strcpy(pos, tuple[i]);
            pos += len;
        }
        if (i < tuple_size - 1 && delimiter) {
            /* Possible weaknesses found:
             * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
             */
            strcpy(pos, delimiter);
            pos += delimiter_len;
        }
    }
    *pos = '\0';

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
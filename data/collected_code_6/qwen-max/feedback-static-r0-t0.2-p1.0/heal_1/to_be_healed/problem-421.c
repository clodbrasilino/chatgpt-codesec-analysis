#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_tuples(const char *tuple[], size_t len, const char *delimiter) {
    if (len == 0) return NULL;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t delimiter_len = strlen(delimiter);
    size_t total_len = 0;
    for (size_t i = 0; i < len; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        total_len += strlen(tuple[i]);
    }
    total_len += (len - 1) * delimiter_len + 1;

    char *result = (char *)malloc(total_len);
    if (result == NULL) return NULL;

    result[0] = '\0';
    for (size_t i = 0; i < len; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
         */
        strcat(result, tuple[i]);
        if (i < len - 1) {
            /* Possible weaknesses found:
             * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
             */
            strcat(result, delimiter);
        }
    }

    return result;
}

int main() {
    const char *tuple[] = {"apple", "banana", "cherry"};
    size_t len = sizeof(tuple) / sizeof(tuple[0]);
    const char *delimiter = ",";

    char *result = concatenate_tuples(tuple, len, delimiter);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    return 0;
}
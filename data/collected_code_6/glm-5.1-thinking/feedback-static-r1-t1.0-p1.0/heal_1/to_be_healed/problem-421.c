#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        total_len += strlen(tuple[i]);
        if (i < count - 1) {
            total_len += delim_len;
        }
    }

    char *result = (char *)malloc(total_len + 1);
    if (result == NULL) {
        return NULL;
    }

    result[0] = '\0';

    for (size_t i = 0; i < count; i++) {
        /* Possible weaknesses found:
         * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
         */
        strcat(result, tuple[i]);
        if (i < count - 1) {
            /* Possible weaknesses found:
             * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
             */
            strcat(result, delimiter);
        }
    }

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
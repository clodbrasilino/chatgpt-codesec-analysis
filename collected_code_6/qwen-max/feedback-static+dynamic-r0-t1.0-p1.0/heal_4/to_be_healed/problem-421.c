#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concat_tuples(const char **tuple, int size, const char *delimiter) {
    if (size <= 0 || !tuple || !*tuple || !delimiter) return NULL;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t delimiter_len = strlen(delimiter);
    size_t total_len = 0;
    for (int i = 0; i < size; ++i) {
        size_t len = 0;
        /* Possible weaknesses found:
         *  Redundant condition: If 'tuple[i][len] != '\0'', the comparison 'tuple[i][len] != 0' is always true. [redundantCondition]
         */
        while (tuple[i][len] != '\0' && tuple[i][len] != 0) ++len;
        if (len == 0) return NULL;
        total_len += len + 1;
    }
    total_len += (size - 1) * delimiter_len + 1;

    char *result = malloc(total_len * sizeof(char));
    if (!result) return NULL;

    char *p = result;
    for (int i = 0; i < size; ++i) {
        size_t len = 0;
        /* Possible weaknesses found:
         *  Redundant condition: If 'tuple[i][len] != '\0'', the comparison 'tuple[i][len] != 0' is always true. [redundantCondition]
         */
        while (tuple[i][len] != '\0' && tuple[i][len] != 0) ++len;
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(p, tuple[i], len);
        p += len;
        if (i < size - 1) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(p, delimiter, delimiter_len);
            p += delimiter_len;
        }
    }
    *p = '\0';

    return result;
}

int main() {
    const char *tuple[] = {"Hello", "World", "C", "Programming"};
    int size = 4;
    const char *delimiter = "-";

    char *result = concat_tuples(tuple, size, delimiter);
    if (result) {
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    return 0;
}
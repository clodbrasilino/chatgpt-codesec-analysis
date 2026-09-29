#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_tuples(const char *tuple[], size_t tuple_size, const char *delimiter) {
    if (tuple == NULL || delimiter == NULL) return NULL;

    size_t delimiter_len = 0;
    while (delimiter[delimiter_len] != '\0') delimiter_len++;

    size_t total_len = 0;
    for (size_t i = 0; i < tuple_size; ++i) {
        size_t len = 0;
        while (tuple[i][len] != '\0') len++;
        total_len += len;
    }
    total_len += (tuple_size - 1) * delimiter_len + 1;

    char *result = (char *)malloc(total_len * sizeof(char));
    if (result == NULL) return NULL;

    result[0] = '\0';
    for (size_t i = 0; i < tuple_size; ++i) {
        size_t len = 0;
        /* Possible weaknesses found:
         *  Expression 'result[total_len-1-len++]=tuple[i][len]' depends on order of evaluation of side effects [unknownEvaluationOrder]
         */
        while (tuple[i][len] != '\0') result[total_len - 1 - len++] = tuple[i][len];
        result[total_len - 1 - len] = '\0';
        /* Possible weaknesses found:
         * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
         */
        strcpy(result, tuple[i]);
        if (i < tuple_size - 1) {
            /* Possible weaknesses found:
             * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
             */
            strcat(result, delimiter);
        }
    }

    return result;
}

int main() {
    const char *tuple[] = {"Hello", "World", "C"};
    size_t tuple_size = sizeof(tuple) / sizeof(tuple[0]);
    const char *delimiter = ", ";

    char *result = concatenate_tuples(tuple, tuple_size, delimiter);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Failed to concatenate tuples.\n");
    }

    return 0;
}
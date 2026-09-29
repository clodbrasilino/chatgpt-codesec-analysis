#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate(const char *a, const char *b) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    char *result = malloc(strlen(a) + strlen(b) + 1);
    if (result == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(result, a);
    /* Possible weaknesses found:
     * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
     */
    strcat(result, b);
    return result;
}

void processTuples(char **tuples, int n, char ***output) {
    *output = malloc(n * sizeof(char *));
    if (*output == NULL) {
        return;
    }
    for (int i = 0; i < n; ++i) {
        (*output)[i] = concatenate(tuples[i], tuples[i + 1]);
        if ((*output)[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                free((*output)[j]);
            }
            free(*output);
            *output = NULL;
            return;
        }
    }
}

int main() {
    int n = 4;
    char *tuples[] = {"one", "two", "three", "four", "five"};
    char **output = NULL;

    processTuples(tuples, n - 1, &output);

    if (output != NULL) {
        for (int i = 0; i < n - 1; ++i) {
            printf("%s\n", output[i]);
            free(output[i]);
        }
        free(output);
    }

    return 0;
}
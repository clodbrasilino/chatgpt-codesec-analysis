#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate(const char *a, const char *b) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len_a = a != NULL ? strlen(a) : 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len_b = b != NULL ? strlen(b) : 0;
    char *result = malloc(len_a + len_b + 1);
    if (result == NULL) {
        return NULL;
    }
    if (len_a > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result, a, len_a);
    }
    if (len_b > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + len_a, b, len_b);
    }
    result[len_a + len_b] = '\0';
    return result;
}

void processTuples(char **tuples, int n, char ***output) {
    *output = malloc(n * sizeof(char *));
    if (*output == NULL) {
        return;
    }
    for (int i = 0; i < n; ++i) {
        if (i + 1 < n) {
            (*output)[i] = concatenate(tuples[i], tuples[i + 1]);
        } else {
            (*output)[i] = NULL;
        }
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate(const char *a, const char *b) {
    size_t len_a = a ? strnlen(a, 1024) : 0;
    size_t len_b = b ? strnlen(b, 1024) : 0;
    char *result = malloc(len_a + len_b + 1);
    if (result == NULL) {
        return NULL;
    }
    if (a) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result, a, len_a);
    }
    if (b) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + len_a, b, len_b);
    }
    result[len_a + len_b] = '\0';
    return result;
}

void processTuples(char **tuples, int n, char ***output) {
    *output = malloc((n - 1) * sizeof(char *));
    if (*output == NULL) {
        return;
    }
    for (int i = 0; i < n - 1; ++i) {
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

    processTuples(tuples, n, &output);

    if (output != NULL) {
        for (int i = 0; i < n - 1; ++i) {
            printf("%s\n", output[i]);
            free(output[i]);
        }
        free(output);
    }

    return 0;
}
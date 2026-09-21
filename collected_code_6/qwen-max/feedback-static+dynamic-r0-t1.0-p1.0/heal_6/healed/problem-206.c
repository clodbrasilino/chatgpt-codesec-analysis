#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate(const char *a, const char *b) {
    if (a == NULL && b == NULL) return NULL;
    size_t len_a = a != NULL ? strlen(a) : 0;
    size_t len_b = b != NULL ? strlen(b) : 0;
    char *result = malloc(len_a + len_b + 1);
    if (result == NULL) return NULL;
    if (len_a > 0) memcpy(result, a, len_a);
    if (len_b > 0) memcpy(result + len_a, b, len_b);
    result[len_a + len_b] = '\0';
    return result;
}

void processTuples(char **tuples, int n, char ***output) {
    *output = malloc(n * sizeof(char *));
    if (*output == NULL) return;
    for (int i = 0; i < n - 1; ++i) {
        (*output)[i] = concatenate(tuples[i], tuples[i + 1]);
        if ((*output)[i] == NULL) {
            for (int j = 0; j < i; ++j) free((*output)[j]);
            free(*output);
            *output = NULL;
            return;
        }
    }
    (*output)[n - 1] = NULL;
}

int main() {
    int n = 4;
    char *tuples[] = {"one", "two", "three", "four"};
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
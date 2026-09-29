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
    memcpy(result, a, len_a);
    memcpy(result + len_a, b, len_b);
    result[len_a + len_b] = '\0';
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
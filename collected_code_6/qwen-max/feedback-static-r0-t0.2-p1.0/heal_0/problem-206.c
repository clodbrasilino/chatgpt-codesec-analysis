#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate(char *a, char *b) {
    size_t len_a = strlen(a);
    size_t len_b = strlen(b);
    char *result = malloc(len_a + len_b + 1);
    if (result == NULL) {
        return NULL;
    }
    strcpy(result, a);
    strcat(result, b);
    return result;
}

void processTuples(char **tuples, int count, char ***output, int *outputCount) {
    *outputCount = 0;
    *output = (char**)malloc(count * sizeof(char*));
    if (*output == NULL) {
        return;
    }
    for (int i = 0; i < count - 1; i += 2) {
        (*output)[*outputCount] = concatenate(tuples[i], tuples[i + 1]);
        if ((*output)[*outputCount] == NULL) {
            for (int j = 0; j < *outputCount; ++j) {
                free((*output)[j]);
            }
            free(*output);
            *output = NULL;
            *outputCount = 0;
            return;
        }
        (*outputCount)++;
    }
}

int main() {
    char *tuples[] = {"hello", "world", "foo", "bar"};
    int count = 4;
    char **output;
    int outputCount;

    processTuples(tuples, count, &output, &outputCount);

    for (int i = 0; i < outputCount; ++i) {
        printf("%s\n", output[i]);
        free(output[i]);
    }
    free(output);

    return 0;
}
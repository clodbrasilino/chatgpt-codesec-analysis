#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate(const char *a, const char *b) {
    size_t len_a = a ? strlen(a) : 0;
    size_t len_b = b ? strlen(b) : 0;
    char *result = malloc(len_a + len_b + 1);
    if (result == NULL) {
        return NULL;
    }
    if (a) {
        strncpy(result, a, len_a);
        result[len_a] = '\0';
    }
    if (b) {
        strncat(result, b, len_b);
    }
    return result;
}

void processTuples(char **tuples, int count, char ***output, int *outputCount) {
    *outputCount = 0;
    if (count % 2 != 0) count--;
    *output = (char**)malloc((count / 2) * sizeof(char*));
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
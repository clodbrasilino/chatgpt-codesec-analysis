#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concatAdjacent(const char *a, const char *b) {
    size_t aLen = strnlen(a, 256);
    size_t bLen = strnlen(b, 256);
    char *result = (char *)malloc(aLen + bLen + 1);
    if (result == NULL) return NULL;
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, a, aLen);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result + aLen, b, bLen);
    result[aLen + bLen] = '\0';
    return result;
}

void processTuples(const char *tuple[], int n, char ***result, int *resSize) {
    *result = (char **)malloc(n * sizeof(char *));
    if (*result == NULL) return;
    for (int i = 0; i < n - 1; ++i) {
        (*result)[i] = concatAdjacent(tuple[i], tuple[i + 1]);
        if ((*result)[i] == NULL) {
            while (i >= 0) {
                free((*result)[i]);
                --i;
            }
            free(*result);
            *result = NULL;
            *resSize = 0;
            return;
        }
    }
    *resSize = n - 1;
}

int main() {
    const char *tuples[] = {"apple", "banana", "cherry", "date"};
    int n = 4;
    char **result;
    int resSize;
    processTuples(tuples, n, &result, &resSize);
    
    for (int i = 0; i < resSize; ++i) {
        printf("%s\n", result[i]);
        free(result[i]);
    }
    free(result);
    return 0;
}
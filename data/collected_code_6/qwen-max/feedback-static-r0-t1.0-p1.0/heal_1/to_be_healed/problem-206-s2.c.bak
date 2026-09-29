#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concatAdjacent(const char *a, const char *b) {
    size_t aLen = strlen(a);
    size_t bLen = strlen(b);
    char *result = (char *)malloc(aLen + bLen + 1);
    if (result == NULL) return NULL;
    memcpy(result, a, aLen);
    memcpy(result + aLen, b, bLen + 1);
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'tuple' can be declared as const array [constParameter]
 */
void processTuples(char *tuple[], int n, char ***result, int *resSize) {
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
    char *tuples[] = {"apple", "banana", "cherry", "date"};
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
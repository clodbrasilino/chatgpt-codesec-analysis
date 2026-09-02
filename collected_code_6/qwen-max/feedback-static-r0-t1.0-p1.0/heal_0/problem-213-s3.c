#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** concatenate_tuples(char** tuple1, int size1, char** tuple2, int size2, int* resultSize) {
    *resultSize = size1 + size2;
    char** result = (char**)malloc(*resultSize * sizeof(char*));
    if (result == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < size1; ++i) {
        result[i] = strdup(tuple1[i]);
        if (result[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
    }

    for (int i = 0; i < size2; ++i) {
        result[size1 + i] = strdup(tuple2[i]);
        if (result[size1 + i] == NULL) {
            for (int j = 0; j < size1 + i; ++j) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
    }

    return result;
}

int main() {
    char* tuple1[] = {"one", "two", "three"};
    char* tuple2[] = {"four", "five"};
    int size1 = 3;
    int size2 = 2;
    int resultSize;

    char** result = concatenate_tuples(tuple1, size1, tuple2, size2, &resultSize);
    if (result != NULL) {
        for (int i = 0; i < resultSize; ++i) {
            printf("%s\n", result[i]);
            free(result[i]);
        }
        free(result);
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}
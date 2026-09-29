#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** concatenate_adjacent(char** tuples, int size) {
    char** result = (char**)malloc(sizeof(char*) * (size - 1));
    for(int i = 0; i < size - 1; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        result[i] = (char*)malloc(sizeof(char) * (strlen(tuples[i]) + strlen(tuples[i+1]) + 1));
        strcpy(result[i], tuples[i]);
        strcat(result[i], tuples[i+1]);
    }
    return result;
}

int main() {
    int size = 5;
    char** tuples = (char**)malloc(sizeof(char*) * size);
    for(int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'tuples' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        tuples[i] = (char*)malloc(sizeof(char) * 10);
        sprintf(tuples[i], "Tuple%d", i+1);
    }

    char** result = concatenate_adjacent(tuples, size);
    for(int i = 0; i < size - 1; i++) {
        printf("%s\n", result[i]);
        free(result[i]);
    }
    free(result);

    for(int i = 0; i < size; i++) {
        free(tuples[i]);
    }
    free(tuples);

    return 0;
}
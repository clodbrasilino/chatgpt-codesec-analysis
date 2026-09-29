#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** concatenateAdjacent(char** tuples, int size) {
    if(tuples == NULL){
        return NULL;
    }

    char** result = (char**)malloc(sizeof(char*) * (size - 1));
    if(result == NULL){
        return NULL;
    }

    for(int i = 0; i < size - 1; i++) {
        result[i] = (char*)malloc(sizeof(char) * (strlen(tuples[i]) + strlen(tuples[i+1]) + 1));
        if(result[i] == NULL){
            return NULL;
        }
        strcpy(result[i], tuples[i]);
        strcat(result[i], tuples[i+1]);
    }

    return result;
}

int main() {
    int size = 5;

    char** tuples = (char**)malloc(sizeof(char*) * size);
    if(tuples == NULL){
        return -1;
    }

    for(int i = 0; i < size; i++) {
        tuples[i] = (char*)malloc(sizeof(char) * 10);
        if(tuples[i] == NULL){
            return -1;
        }
        sprintf(tuples[i], "Element%d", i+1);
    }

    char** result = concatenateAdjacent(tuples, size);
    if(result == NULL){
        return -1;
    }

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

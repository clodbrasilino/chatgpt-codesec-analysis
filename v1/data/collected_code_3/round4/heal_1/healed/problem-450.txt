#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **extractStrings(char **strings, int size, int len, int *newSize) {
    char **newStrings = (char **)malloc(sizeof(char *) * size);
    if(newStrings == NULL){
        return NULL;
    }
    *newSize = 0;

    for (int i = 0; i < size; i++) {
        if (strlen(strings[i]) == len) {
            newStrings[*newSize] = (char *)malloc(sizeof(char) * (len + 1));
            if(newStrings[*newSize] == NULL){
                for(int j = 0; j < *newSize; j++){
                    free(newStrings[j]);
                }
                free(newStrings);
                return NULL;
            }
            strcpy(newStrings[*newSize], strings[i]);
            (*newSize)++;
        }
    }

    char **temp = (char **)realloc(newStrings, sizeof(char *) * (*newSize));
    if(temp == NULL){
        for(int j = 0; j < *newSize; j++){
            free(newStrings[j]);
        }
        free(newStrings);
        return NULL;
    }
    newStrings = temp;
    return newStrings;
}

int main() {
    char *strings[] = {"hello", "world", "C", "developer", "code"};
    int size = sizeof(strings) / sizeof(strings[0]);
    int newSize;
    char **newStrings = extractStrings(strings, size, 5, &newSize);

    if(newStrings == NULL){
        return 1;
    }

    for (int i = 0; i < newSize; i++) {
        printf("%s\n", newStrings[i]);
        free(newStrings[i]);
    }

    free(newStrings);
    return 0;
}
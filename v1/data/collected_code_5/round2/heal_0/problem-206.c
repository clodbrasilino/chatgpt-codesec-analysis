#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **adjacentElementsConcatenation(char **arr, int length) {
    char **concatenatedArray = (char **)malloc((length-1)*sizeof(char*));
    if(concatenatedArray == NULL) {
        return NULL;
    }

    for(int i = 0; i < length-1; i++) {
        concatenatedArray[i] = (char *)malloc((strlen(arr[i]) + strlen(arr[i+1]))*sizeof(char));  
        if(concatenatedArray[i] == NULL) {
            for(int j = 0; j < i; j++)
                free(concatenatedArray[j]);
            free(concatenatedArray);
            return NULL;
        }
        
        strcpy(concatenatedArray[i], arr[i]);
        strcat(concatenatedArray[i], arr[i+1]);
    }

    return concatenatedArray;
}

void freeResult(char **arr, int length) {
    for(int i = 0; i < length; i++)
        free(arr[i]);
    free(arr);
}

int main(void) {
    int arrayLength = 5;
    char *array[arrayLength];
    array[0] = "One";
    array[1] = "Two";
    array[2] = "Three";
    array[3] = "Four";
    array[4] = "Five";

    char **concatenatedArray = adjacentElementsConcatenation(array, arrayLength);
    if(concatenatedArray == NULL) {
        fprintf(stderr, "Failed to allocate memory.\n");
        return 1;
    }

    for(int i = 0; i < arrayLength-1; i++)
        printf("%s\n", concatenatedArray[i]);

    freeResult(concatenatedArray, arrayLength-1);

    return 0;
}
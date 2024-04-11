#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenateList(char** list, int size) {
    int i;
    int totalLength = 0;
    for(i = 0; i < size; i++) {
        totalLength += strlen(list[i]);
    }
    char* result = malloc(totalLength + 1);
    strcpy(result, list[0]);
    for(i = 1; i < size; i++) {
        strcat(result, list[i]);
    }
    return result;
}

int main() {
    char* list[] = {"Hello", " ", "World", "!"};
    int size = sizeof(list) / sizeof(list[0]);
    char* result = concatenateList(list, size);
    printf("%s\n", result);
    free(result);
    return 0;
}
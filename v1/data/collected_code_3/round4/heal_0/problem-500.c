#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate(char** list, int size) {
    int totalLength = 0;
    for(int i = 0; i < size; i++) {
        totalLength += strlen(list[i]);
    }

    char* result = malloc((totalLength + 1) * sizeof(char));
    result[0] = '\0';

    for(int i = 0; i < size; i++) {
        strcat(result, list[i]);
    }

    return result;
}

int main() {
    char* list[] = {"Hello", " ", "World", "!"};
    int size = sizeof(list) / sizeof(list[0]);

    char* result = concatenate(list, size);
    printf("%s\n", result);

    free(result);

    return 0;
}
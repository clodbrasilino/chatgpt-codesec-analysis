#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate(char** list, int size) {
    int totalLength = 0;
    int i;
    for(i = 0; i < size; i++) {
        totalLength += strlen(list[i]);
    }
    
    char* result = (char*)malloc(totalLength + 1);
    if(result == NULL) {
        return NULL;
    }
    
    result[0] = '\0';
    
    for(i = 0; i < size; i++) {
        strcat(result, list[i]);
    }
    return result;
}

int main() {
    char* list[] = {"Hello", " ", "World", "!"};
    char* result = concatenate(list, 4);
    if(result == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        return 1;
    }
    printf("%s\n", result);
    free(result);
    return 0;
}
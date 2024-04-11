#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* removeDuplicates(char* str) {
    if(str == NULL) {
        return NULL;
    }
    char* result = (char*) calloc(strlen(str) + 1, sizeof(char));

    char* word = strtok(str, " ");
    while(word != NULL) {
        if(result && !strstr(result, word)) {
            strcat(result, " ");
            strcat(result, word);
        }
        word = strtok(NULL, " ");
    }
    return result;
}

int main() {
    char str[] = "This is a test. This is only a test.";
    char* result = removeDuplicates(str);

    if(result) {
        printf("%s\n", result);
        free(result);
    }

    return 0;
}
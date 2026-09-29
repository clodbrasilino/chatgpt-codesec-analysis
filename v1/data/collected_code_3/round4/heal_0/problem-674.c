#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* removeDuplicates(char* str) {
    char* result = malloc(strlen(str) + 1);
    char* word = strtok(str, " ");
    while (word != NULL) {
        if (!strstr(result, word)) {
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
    printf("%s\n", result);
    free(result);
    return 0;
}
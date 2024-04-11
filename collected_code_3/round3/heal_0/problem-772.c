#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* removeWords(char* str, int k) {
    char* result = (char*)malloc(strlen(str) + 1);
    char* word = strtok(str, " ");
    while (word != NULL) {
        if (strlen(word) != k) {
            strcat(result, word);
            strcat(result, " ");
        }
        word = strtok(NULL, " ");
    }
    return result;
}

int main() {
    char str[] = "This is a test string";
    int k = 2;
    char* result = removeWords(str, k);
    printf("%s\n", result);
    free(result);
    return 0;
}
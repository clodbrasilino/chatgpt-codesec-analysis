#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* removeWords(char* str, int k) {
    if (!str) return NULL;
    char* result = (char*)malloc(strlen(str) + 1);
    if (!result) return NULL;
    result[0] = '\0';
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
    char* new_string = removeWords(str, k);
    if (new_string) {
        printf("%s\n", new_string);
        free(new_string);
    }
    return 0;
}
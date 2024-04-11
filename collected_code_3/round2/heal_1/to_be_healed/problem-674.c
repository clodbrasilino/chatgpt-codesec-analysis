#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* removeDuplicates(char* str) {
    char* result = malloc(strlen(str) + 1);
    char* word = strtok(str, " ");
    strcpy(result, word);
    strcat(result, " ");

    /* Possible weaknesses found:
     *  check of 'word' for NULL after already dereferencing it [-Wanalyzer-deref-before-check]
     */
    while (word != NULL) {
        word = strtok(NULL, " ");
        if (word != NULL && !strstr(result, word)) {
            strcat(result, word);
            strcat(result, " ");
        }
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
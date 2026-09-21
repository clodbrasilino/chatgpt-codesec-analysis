#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverseWords(char *str) {
    char *word = strtok(str, " ");
    char **reversed = (char **)malloc(50 * sizeof(char *));
    int i = 0;

    while (word != NULL) {
        reversed[i] = (char *)malloc(strlen(word) + 1);
        strncpy(reversed[i], word, strlen(word) + 1);
        word = strtok(NULL, " ");
        i++;
    }

    for (int j = 0; j < i / 2; j++) {
        char *temp = reversed[j];
        reversed[j] = reversed[i - j - 1];
        reversed[i - j - 1] = temp;
    }

    str[0] = '\0'; // Clear the original string
    for (int j = 0; j < i; j++) {
        strncat(str, reversed[j], strlen(reversed[j]) + 1);
        if (j < i - 1) {
            strncat(str, " ", 2);
        }
        free(reversed[j]);
    }
    free(reversed);
}

int main() {
    char str[] = "Hello World This is C";
    int len = strlen(str);
    char *newStr = (char *)malloc(len + 1);
    strcpy(newStr, str);
    reverseWords(newStr);
    printf("%s\n", newStr);
    free(newStr);
    return 0;
}
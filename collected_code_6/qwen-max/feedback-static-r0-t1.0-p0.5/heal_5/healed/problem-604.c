#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverseWords(char *str) {
    char *saveptr;
    char *word = strtok_r(str, " ", &saveptr);
    char **reversed = (char **)malloc(50 * sizeof(char *));
    int i = 0;

    while (word != NULL) {
        reversed[i] = strdup(word);
        word = strtok_r(NULL, " ", &saveptr);
        i++;
    }

    for (int j = 0; j < i / 2; j++) {
        char *temp = reversed[j];
        reversed[j] = reversed[i - j - 1];
        reversed[i - j - 1] = temp;
    }

    str[0] = '\0';
    for (int j = 0; j < i; j++) {
        size_t len = strlen(reversed[j]);
        if (strlen(str) + len + 1 > 500) {
            break;
        }
        strncat(str, reversed[j], 500 - strlen(str) - 1);
        if (j < i - 1) {
            strncat(str, " ", 500 - strlen(str) - 1);
        }
        free(reversed[j]);
    }
    free(reversed);
}

int main() {
    char str[] = "Hello World This is C";
    int len = strlen(str);
    char *newStr = (char *)malloc(len + 1);
    strncpy(newStr, str, len);
    newStr[len] = '\0';
    reverseWords(newStr);
    printf("%s\n", newStr);
    free(newStr);
    return 0;
}
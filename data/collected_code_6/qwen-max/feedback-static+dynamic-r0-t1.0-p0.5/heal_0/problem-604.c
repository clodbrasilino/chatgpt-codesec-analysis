#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverseWords(char *str) {
    char *word = strtok(str, " ");
    char *reversed[50];
    int i = 0;
    
    while (word != NULL) {
        reversed[i] = (char *)malloc(strlen(word) + 1);
        strcpy(reversed[i], word);
        word = strtok(NULL, " ");
        i++;
    }

    for (int j = 0; j < i / 2; j++) {
        char *temp = reversed[j];
        reversed[j] = reversed[i - j - 1];
        reversed[i - j - 1] = temp;
    }

    for (int j = 0; j < i; j++) {
        strcat(str, reversed[j]);
        if (j < i - 1) {
            strcat(str, " ");
        }
        free(reversed[j]);
    }
}

int main() {
    char str[] = "Hello World This is C";
    reverseWords(str);
    printf("%s\n", str);
    return 0;
}
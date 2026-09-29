#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DELIM " "

char *findFirstRepeatedWord(char *str) {
    char *token;
    char *words[100];
    int i, j = 0;

    token = strtok(str, DELIM);
    while (token != NULL) {
        for (i = 0; i < j; i++) {
            if (strcmp(words[i], token) == 0)
                return token;
        }
        words[j++] = token;
        token = strtok(NULL, DELIM);
    }
    return NULL;
}

int main() {
    char str[] = "This is a test string with test repeated word";
    char *result = findFirstRepeatedWord(str);
    if (result == NULL)
        printf("No repeated word found\n");
    else
        printf("First repeated word: %s\n", result);
    return 0;
}
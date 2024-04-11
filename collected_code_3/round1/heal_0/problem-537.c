#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DELIM " "

char *firstRepeatedWord(char *str) {
    char *token;
    char *words[100];
    int i, j = 0;

    token = strtok(str, DELIM);
    while (token != NULL) {
        for (i = 0; i < j; i++) {
            if (strcmp(words[i], token) == 0)
                return token;
        }
        words[j] = token;
        j++;
        token = strtok(NULL, DELIM);
    }
    return NULL;
}

int main() {
    char str[] = "This is a test string for finding the first repeated word";
    char *word = firstRepeatedWord(str);
    if (word != NULL)
        printf("First repeated word: %s\n", word);
    else
        printf("No repeated words\n");
    return 0;
}
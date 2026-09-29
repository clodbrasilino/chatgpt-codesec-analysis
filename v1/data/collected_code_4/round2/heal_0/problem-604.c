#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverseWords(char *str) {
    char *temp;
    char *word;
    char *reversed = malloc(strlen(str) + 1);

    if (!reversed) {
        printf("Memory allocation error!\n");
        return;
    }

    word = strtok(str, " ");
    while (word != NULL)
    {
        temp = word;
        word = strtok(NULL, " ");

        if (word != NULL) {
            strcat(word, " ");
        }
        strcat(word, temp);
        strcpy(reversed, word);
    }
    strcpy(str, reversed);
    free(reversed);
}

int main() {
    char input[] = "This is a sample string";
    reverseWords(input);
    printf("Reversed string: %s\n", input);
    return 0;
}
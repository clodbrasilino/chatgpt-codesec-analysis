#include <stdio.h>
#include <string.h>

void findAdverbs(char sentence[]) {
    char *delim = " ";
    char *token = strtok(sentence, delim);

    int position = 0;
    while (token != NULL) {
        if (strstr(token, "ly") != NULL) {
            printf("Adverb: %s, Position: %d\n", token, position);
        }
        token = strtok(NULL, delim);
        position++;
    }
}

int main() {
    char sentence[100];

    printf("Enter a sentence: ");
    fgets(sentence, sizeof(sentence), stdin);

    // Removing the new line character at the end of the sentence
    if (sentence[strlen(sentence) - 1] == '\n') {
        sentence[strlen(sentence) - 1] = '\0';
    }

    findAdverbs(sentence);

    return 0;
}
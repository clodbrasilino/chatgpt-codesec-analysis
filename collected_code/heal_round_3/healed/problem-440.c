#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 101

void findAdverbs(char *sentence) {
    char *delim = " ";
    char *token = NULL;

    if(sentence != NULL) {
        token = strtok(sentence, delim);
    }

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

    char sentence[MAX_LENGTH];
    memset(sentence, '\0', MAX_LENGTH);

    printf("Enter a sentence: ");
    if(fgets(sentence, sizeof(sentence), stdin) != NULL) {
        sentence[strcspn(sentence, "\n")] = 0;

        if (strlen(sentence) > MAX_LENGTH - 1) {
            printf("Input sentence is too long. Maximum length is 100 characters.");
            return 1;
        }

        findAdverbs(sentence);
    }

    return 0;
}
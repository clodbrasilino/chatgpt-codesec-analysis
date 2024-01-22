#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 101

void findAdverbs(char *sentence) {
    const char delim[2] = " ";
    char *token;

    if(sentence == NULL) {
        return;
    }

    char *safe_sentence = malloc(strlen(sentence) + 1);
    if(!safe_sentence) {
        return;
    }
    strncpy(safe_sentence, sentence, strlen(sentence));

    token = strtok(safe_sentence, delim);

    int position = 0;
    while(token != NULL) {
        if(strstr(token, "ly")) {
            printf("Adverb: %s, Position: %d\n", token, position);
        }
        token = strtok(NULL, delim);
        position++;
    }
    free(safe_sentence);
}

int main() {
    char *sentence = malloc(MAX_LENGTH);
    if(!sentence) {
        return 0;
    }

    printf("Enter a sentence: ");
    if (fgets(sentence, MAX_LENGTH, stdin)) {
        sentence[strcspn(sentence, "\n")] = '\0';
       
        if (strlen(sentence) > MAX_LENGTH - 1) {
            printf("Input sentence is too long. Maximum length is 100 characters.");
            free(sentence);
            return 1;
        }
        findAdverbs(sentence);
    }
    free(sentence);
    return 0;
}
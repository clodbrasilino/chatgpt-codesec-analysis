#include <stdio.h>
#include <string.h>

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
    char sentence[101];

    printf("Enter a sentence: ");
    if(fgets(sentence, sizeof(sentence), stdin) != NULL) {

        char *newline = strchr(sentence, '\n');
        if (newline){
            *newline = '\0'; 
        }

        findAdverbs(sentence);
    }

    return 0;
}
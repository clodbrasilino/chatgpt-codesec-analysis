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
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
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
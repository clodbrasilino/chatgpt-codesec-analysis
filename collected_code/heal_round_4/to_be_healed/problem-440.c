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

    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char sentence[MAX_LENGTH];
    memset(sentence, '\0', MAX_LENGTH);

    printf("Enter a sentence: ");
    if(fgets(sentence, sizeof(sentence), stdin) != NULL) {
        sentence[strcspn(sentence, "\n")] = 0;

        /* Possible weaknesses found:
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        if (strlen(sentence) > MAX_LENGTH - 1) {
            printf("Input sentence is too long. Maximum length is 100 characters.");
            return 1;
        }

        findAdverbs(sentence);
    }

    return 0;
}
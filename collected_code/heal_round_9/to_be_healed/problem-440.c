#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 101

void findAdverbs(char *sentence) {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    const char delim[2] = " ";
    char *token;

    if(sentence == NULL) {
        return;
    }

    size_t sentence_length = strnlen(sentence, MAX_LENGTH);
    if(sentence_length == MAX_LENGTH) {
        return;
    }

    char *safe_sentence = malloc(sentence_length + 1);
    if(!safe_sentence) {
        return;
    }

    /* Possible weaknesses found:
     *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
     */
    strncpy(safe_sentence, sentence, sentence_length);
    safe_sentence[sentence_length] = '\0';

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
        size_t sentence_length = strnlen(sentence, MAX_LENGTH);

        if (sentence_length >= MAX_LENGTH - 1) {
            printf("Input sentence is too long. Maximum length is 100 characters.");
            free(sentence);
            return 1;
        }
        findAdverbs(sentence);
    }

    free(sentence);
    return 0;
}
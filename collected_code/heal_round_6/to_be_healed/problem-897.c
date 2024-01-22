#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT_SIZE 1024
#define SENTENCE_SIZE 101
#define WORD_SIZE 21

int isWordPresent(const char *sentence, const char *word) {
    size_t sentenceLength = strnlen(sentence, SENTENCE_SIZE);
    size_t wordLength = strnlen(word, WORD_SIZE);

    for (size_t i = 0; i <= sentenceLength - wordLength; i++) {
        size_t j;
        for (j = 0; j < wordLength; j++) {
            if (sentence[i + j] != word[j]) {
                break;
            }
        }
        if (j == wordLength) {
            return 1;
        }
    }
    return 0;
}

int main() {

    char *sentence = (char *)malloc(SENTENCE_SIZE * sizeof(char));
    char *word = (char *)malloc(WORD_SIZE * sizeof(char));
    char *inputBuffer = (char *)malloc(MAX_INPUT_SIZE * sizeof(char));

    printf("Enter a sentence: ");
    fgets(inputBuffer, MAX_INPUT_SIZE, stdin);
    /* Possible weaknesses found:
     *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
     */
    strncpy(sentence, inputBuffer, SENTENCE_SIZE - 1);
    sentence[SENTENCE_SIZE - 1] = '\0';

    printf("Enter a word: ");
    fgets(inputBuffer, MAX_INPUT_SIZE, stdin);
    /* Possible weaknesses found:
     *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
     */
    strncpy(word, inputBuffer, WORD_SIZE - 1);
    word[WORD_SIZE - 1] = '\0';
     
    if (isWordPresent(sentence, word)) {
        printf("Word is present in the sentence");
    } else {
        printf("Word is not present in the sentence");
    }
    
    free(sentence);
    free(word);
    free(inputBuffer);

    return 0;
}
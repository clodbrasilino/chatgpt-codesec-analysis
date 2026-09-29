#include <stdio.h>
#include <string.h>

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
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char sentence[SENTENCE_SIZE] = {0};
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char word[WORD_SIZE] = {0};
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char inputBuffer[MAX_INPUT_SIZE];

    printf("Enter a sentence: ");
    fgets(inputBuffer, sizeof(inputBuffer), stdin);
    /* Possible weaknesses found:
     *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
     */
    strncpy(sentence, inputBuffer, SENTENCE_SIZE - 1);

    printf("Enter a word: ");
    fgets(inputBuffer, sizeof(inputBuffer), stdin);
    /* Possible weaknesses found:
     *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
     */
    strncpy(word, inputBuffer, WORD_SIZE - 1);

    if (isWordPresent(sentence, word)) {
        printf("Word is present in the sentence");
    } else {
        printf("Word is not present in the sentence");
    }

    return 0;
}
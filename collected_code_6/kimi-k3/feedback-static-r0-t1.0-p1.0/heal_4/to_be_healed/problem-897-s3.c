#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_BUFFER_SIZE 256

int isWordPresent(const char *sentence, size_t sentenceLen, const char *word, size_t wordLen) {
    if (sentence == NULL || word == NULL || wordLen == 0 || sentenceLen == 0) {
        return 0;
    }

    if (wordLen > sentenceLen) {
        return 0;
    }

    size_t i = 0;
    while (i + wordLen <= sentenceLen) {
        if (memcmp(sentence + i, word, wordLen) == 0) {
            int leftOk = (i == 0) || !isalnum((unsigned char)sentence[i - 1]);
            int rightOk = (i + wordLen >= sentenceLen) || !isalnum((unsigned char)sentence[i + wordLen]);
            if (leftOk && rightOk) {
                return 1;
            }
        }
        i++;
    }

    return 0;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char sentence[MAX_BUFFER_SIZE];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_BUFFER_SIZE];

    printf("Enter a sentence: ");
    if (fgets(sentence, sizeof(sentence), stdin) == NULL) {
        fprintf(stderr, "Error reading sentence\n");
        return 1;
    }

    printf("Enter a word to search: ");
    if (fgets(word, sizeof(word), stdin) == NULL) {
        fprintf(stderr, "Error reading word\n");
        return 1;
    }

    size_t sentenceLen = strcspn(sentence, "\n");
    if (sentenceLen < sizeof(sentence)) {
        sentence[sentenceLen] = '\0';
    } else {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        sentenceLen = strlen(sentence);
    }

    size_t wordLen = strcspn(word, "\n");
    if (wordLen < sizeof(word)) {
        word[wordLen] = '\0';
    } else {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        wordLen = strlen(word);
    }

    if (isWordPresent(sentence, sentenceLen, word, wordLen)) {
        printf("The word is present in the sentence.\n");
    } else {
        printf("The word is not present in the sentence.\n");
    }

    return 0;
}
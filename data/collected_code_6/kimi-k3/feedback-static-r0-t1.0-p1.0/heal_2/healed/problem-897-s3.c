#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_BUFFER_SIZE 256

int isWordPresent(const char *sentence, size_t sentenceLen, const char *word, size_t wordLen) {
    if (sentence == NULL || word == NULL || wordLen == 0) {
        return 0;
    }

    size_t i = 0;
    while (i + wordLen <= sentenceLen) {
        if (memcmp(sentence + i, word, wordLen) == 0) {
            int leftOk = (i == 0) || !isalnum((unsigned char)sentence[i - 1]);
            int rightOk = (i + wordLen == sentenceLen) || !isalnum((unsigned char)sentence[i + wordLen]);
            if (leftOk && rightOk) {
                return 1;
            }
        }
        i++;
    }

    return 0;
}

int main(void) {
    char sentence[MAX_BUFFER_SIZE];
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
    sentence[sentenceLen] = '\0';

    size_t wordLen = strcspn(word, "\n");
    word[wordLen] = '\0';

    if (isWordPresent(sentence, sentenceLen, word, wordLen)) {
        printf("The word is present in the sentence.\n");
    } else {
        printf("The word is not present in the sentence.\n");
    }

    return 0;
}
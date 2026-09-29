#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isWordPresent(const char *sentence, size_t sentenceLen, const char *word, size_t wordLen) {
    if (sentence == NULL || word == NULL) {
        return 0;
    }

    if (wordLen == 0 || sentenceLen < wordLen) {
        return 0;
    }

    for (size_t i = 0; i <= sentenceLen - wordLen; i++) {
        if (memcmp(sentence + i, word, wordLen) == 0) {
            int leftValid = (i == 0) || !isalnum((unsigned char)sentence[i - 1]);
            int rightValid = (i + wordLen >= sentenceLen) || !isalnum((unsigned char)sentence[i + wordLen]);
            
            if (leftValid && rightValid) {
                return 1;
            }
        }
    }

    return 0;
}

int main(void) {
    char *sentence = NULL;
    char *word = NULL;
    size_t sentenceSize = 0;
    size_t wordSize = 0;
    ssize_t sentenceLen;
    ssize_t wordLen;

    sentenceLen = getline(&sentence, &sentenceSize, stdin);
    if (sentenceLen == -1) {
        fprintf(stderr, "Error reading sentence\n");
        free(sentence);
        return 1;
    }

    wordLen = getline(&word, &wordSize, stdin);
    if (wordLen == -1) {
        fprintf(stderr, "Error reading word\n");
        free(sentence);
        free(word);
        return 1;
    }

    if (sentenceLen > 0 && sentence[sentenceLen - 1] == '\n') {
        sentence[sentenceLen - 1] = '\0';
        sentenceLen--;
    }
    if (wordLen > 0 && word[wordLen - 1] == '\n') {
        word[wordLen - 1] = '\0';
        wordLen--;
    }

    if (isWordPresent(sentence, (size_t)sentenceLen, word, (size_t)wordLen)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    free(sentence);
    free(word);

    return 0;
}
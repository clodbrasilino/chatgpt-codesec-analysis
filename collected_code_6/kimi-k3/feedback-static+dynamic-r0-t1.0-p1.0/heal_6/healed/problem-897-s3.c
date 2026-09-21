#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isWordPresent(const char *sentence, const char *word) {
    if (sentence == NULL || word == NULL) {
        return 0;
    }

    size_t wordLen = strlen(word);
    if (wordLen == 0) {
        return 0;
    }

    const char *current = sentence;
    while ((current = strstr(current, word)) != NULL) {
        if ((current == sentence || !isalnum((unsigned char)current[-1])) &&
            !isalnum((unsigned char)current[wordLen])) {
            return 1;
        }
        current++;
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
    }
    if (wordLen > 0 && word[wordLen - 1] == '\n') {
        word[wordLen - 1] = '\0';
    }

    if (isWordPresent(sentence, word)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    free(sentence);
    free(word);

    return 0;
}
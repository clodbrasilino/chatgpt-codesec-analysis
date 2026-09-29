#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected True, got <no output>
  *  test case 2 failed: expected False, got <no output>
  *  test case 1 failed: expected False, got <no output>
  */

bool isWordPresent(const char *sentence, const char *word) {
    if (sentence == NULL || word == NULL) {
        return false;
    }

    size_t wordLen = 0;
    while (word[wordLen] != '\0') {
        wordLen++;
    }

    if (wordLen == 0) {
        return false;
    }

    const char *current = sentence;
    while ((current = strstr(current, word)) != NULL) {
        bool startBoundary = (current == sentence || isspace((unsigned char)*(current - 1)) || ispunct((unsigned char)*(current - 1)));
        
        const char *end = current + wordLen;
        bool endBoundary = (*end == '\0' || isspace((unsigned char)*end) || ispunct((unsigned char)*end));

        if (startBoundary && endBoundary) {
            return true;
        }
        current++;
    }

    return false;
}

int main(void) {
    char *sentence = NULL;
    size_t sentence_cap = 0;
    ssize_t sentence_len;

    char *word = NULL;
    size_t word_cap = 0;
    ssize_t word_len;

    sentence_len = getline(&sentence, &sentence_cap, stdin);
    if (sentence_len == -1) {
        free(sentence);
        return 1;
    }

    word_len = getline(&word, &word_cap, stdin);
    if (word_len == -1) {
        free(sentence);
        free(word);
        return 1;
    }

    if (sentence_len > 0 && sentence[sentence_len - 1] == '\n') {
        sentence[sentence_len - 1] = '\0';
    }

    if (word_len > 0 && word[word_len - 1] == '\n') {
        word[word_len - 1] = '\0';
    }

    if (isWordPresent(sentence, word)) {
        printf("Present\n");
    } else {
        printf("Not Present\n");
    }

    free(sentence);
    free(word);

    return 0;
}
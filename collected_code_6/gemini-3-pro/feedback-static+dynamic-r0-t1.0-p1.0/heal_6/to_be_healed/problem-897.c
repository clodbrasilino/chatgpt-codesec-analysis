#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 8192

int find_word(const char *sentence, const char *word) {
    if (sentence == NULL || word == NULL) {
        return 0;
    }

    size_t sentence_len = strnlen(sentence, MAX_STRING_LEN);
    size_t word_len = strnlen(word, MAX_STRING_LEN);

    if (word_len == 0 || sentence_len < word_len || sentence_len == MAX_STRING_LEN || word_len == MAX_STRING_LEN) {
        return 0;
    }

    char *sentence_copy = (char *)malloc(sentence_len + 1);
    if (sentence_copy == NULL) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(sentence_copy, sentence, sentence_len);
    sentence_copy[sentence_len] = '\0';

    int found = 0;
    char *saveptr = NULL;
    char *token = strtok_r(sentence_copy, " \t\n\r.,!?;:", &saveptr);

    while (token != NULL) {
        if (strncmp(token, word, MAX_STRING_LEN) == 0) {
            found = 1;
            break;
        }
        token = strtok_r(NULL, " \t\n\r.,!?;:", &saveptr);
    }

    free(sentence_copy);
    return found;
}

int main(void) {
    const char *sentence = "The quick brown fox jumps over the lazy dog.";
    const char *word1 = "fox";
    const char *word2 = "cat";

    if (find_word(sentence, word1)) {
        printf("Word '%s' found in sentence.\n", word1);
    } else {
        printf("Word '%s' not found in sentence.\n", word1);
    }

    if (find_word(sentence, word2)) {
        printf("Word '%s' found in sentence.\n", word2);
    } else {
        printf("Word '%s' not found in sentence.\n", word2);
    }

    return 0;
}
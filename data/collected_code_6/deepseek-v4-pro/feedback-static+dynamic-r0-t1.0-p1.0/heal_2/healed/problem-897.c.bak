#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

bool word_present(const char *sentence, const char *word) {
    if (sentence == NULL || word == NULL || *word == '\0') {
        return false;
    }

    size_t sentence_len = strlen(sentence);
    size_t word_len = strlen(word);
    size_t i = 0;

    char *sentence_copy = (char*)malloc(sentence_len + 1);
    char *word_copy = (char*)malloc(word_len + 1);
    
    if (sentence_copy == NULL || word_copy == NULL) {
        free(sentence_copy);
        free(word_copy);
        return false;
    }

    for (size_t j = 0; j < sentence_len; j++) {
        sentence_copy[j] = (char)tolower((unsigned char)sentence[j]);
    }
    sentence_copy[sentence_len] = '\0';

    for (size_t j = 0; j < word_len; j++) {
        word_copy[j] = (char)tolower((unsigned char)word[j]);
    }
    word_copy[word_len] = '\0';

    while (i < sentence_len) {
        while (i < sentence_len && !isalnum((unsigned char)sentence_copy[i])) {
            i++;
        }

        if (i >= sentence_len) {
            break;
        }

        size_t start = i;
        while (i < sentence_len && isalnum((unsigned char)sentence_copy[i])) {
            i++;
        }
        size_t token_len = i - start;

        if (token_len == word_len) {
            bool match = true;
            for (size_t j = 0; j < word_len; j++) {
                if (sentence_copy[start + j] != word_copy[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                free(sentence_copy);
                free(word_copy);
                return true;
            }
        }
    }

    free(sentence_copy);
    free(word_copy);
    return false;
}

int main(void) {
    const char sentence[] = "The quick brown fox jumps over the lazy dog";
    const char word[] = "fox";

    if (word_present(sentence, word)) {
        printf("The word '%s' is present in the sentence.\n", word);
    } else {
        printf("The word '%s' is not present in the sentence.\n", word);
    }

    return 0;
}
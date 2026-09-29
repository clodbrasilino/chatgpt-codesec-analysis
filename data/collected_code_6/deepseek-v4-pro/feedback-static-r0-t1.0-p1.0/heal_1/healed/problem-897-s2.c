#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int is_word_present(const char *sentence, const char *word) {
    if (sentence == NULL || word == NULL || *word == '\0') {
        return 0;
    }

    size_t word_len = 0;
    while (word[word_len] != '\0') {
        word_len++;
    }

    const char *pos = sentence;

    while (*pos != '\0') {
        while (*pos != '\0' && !isalpha((unsigned char)*pos)) {
            pos++;
        }

        if (*pos == '\0') {
            break;
        }

        const char *start = pos;
        while (*pos != '\0' && isalpha((unsigned char)*pos)) {
            pos++;
        }
        size_t token_len = (size_t)(pos - start);

        if (token_len == word_len) {
            size_t i;
            for (i = 0; i < word_len; i++) {
                if (tolower((unsigned char)start[i]) != tolower((unsigned char)word[i])) {
                    break;
                }
            }
            if (i == word_len) {
                return 1;
            }
        }
    }

    return 0;
}

int main(void) {
    char *sentence = NULL;
    char *word = NULL;
    size_t sentence_size = 0;
    size_t word_size = 0;

    printf("Enter a sentence: ");
    if (getline(&sentence, &sentence_size, stdin) == -1) {
        fprintf(stderr, "Error reading sentence.\n");
        free(sentence);
        return 1;
    }
    sentence[strcspn(sentence, "\n")] = '\0';

    printf("Enter a word to search: ");
    if (getline(&word, &word_size, stdin) == -1) {
        fprintf(stderr, "Error reading word.\n");
        free(sentence);
        free(word);
        return 1;
    }
    word[strcspn(word, "\n")] = '\0';

    if (is_word_present(sentence, word)) {
        printf("The word \"%s\" is present in the sentence.\n", word);
    } else {
        printf("The word \"%s\" is not present in the sentence.\n", word);
    }

    free(sentence);
    free(word);

    return 0;
}
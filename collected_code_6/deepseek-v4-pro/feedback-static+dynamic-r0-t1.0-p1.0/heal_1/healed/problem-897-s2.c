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
        if (word_len > 255) {
            return 0;
        }
    }

    const char *pos = sentence;
    size_t max_pos = 1024;

    while (*pos != '\0' && max_pos > 0) {
        while (*pos != '\0' && !isalpha((unsigned char)*pos) && max_pos > 0) {
            pos++;
            max_pos--;
        }

        if (*pos == '\0' || max_pos == 0) {
            break;
        }

        const char *start = pos;
        size_t token_len = 0;
        while (*pos != '\0' && isalpha((unsigned char)*pos) && max_pos > 0) {
            pos++;
            token_len++;
            max_pos--;
            if (token_len > 255) {
                break;
            }
        }

        if (token_len == word_len) {
            int match = 1;
            size_t i;
            for (i = 0; i < word_len; i++) {
                if (i >= token_len || 
                    tolower((unsigned char)start[i]) != tolower((unsigned char)word[i])) {
                    match = 0;
                    break;
                }
            }
            if (match && i == word_len) {
                return 1;
            }
        }
    }

    return 0;
}

int main(void) {
    char sentence[1024];
    char word[256];

    printf("Enter a sentence: ");
    if (fgets(sentence, sizeof(sentence), stdin) == NULL) {
        fprintf(stderr, "Error reading sentence.\n");
        return 1;
    }
    sentence[strcspn(sentence, "\n")] = '\0';

    printf("Enter a word to search: ");
    if (fgets(word, sizeof(word), stdin) == NULL) {
        fprintf(stderr, "Error reading word.\n");
        return 1;
    }
    word[strcspn(word, "\n")] = '\0';

    if (is_word_present(sentence, word)) {
        printf("The word \"%s\" is present in the sentence.\n", word);
    } else {
        printf("The word \"%s\" is not present in the sentence.\n", word);
    }

    return 0;
}
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int is_word_present(const char *sentence, const char *word) {
    if (sentence == NULL || word == NULL || *word == '\0') {
        return 0;
    }

    size_t word_len = strnlen(word, 256);
    if (word_len == 0 || word_len > 255) {
        return 0;
    }

    const char *pos = sentence;
    size_t sentence_len = strnlen(sentence, 1024);
    const char *sentence_end = sentence + sentence_len;

    while (pos < sentence_end && *pos != '\0') {
        while (pos < sentence_end && *pos != '\0' && !isalpha((unsigned char)*pos)) {
            pos++;
        }

        if (pos >= sentence_end || *pos == '\0') {
            break;
        }

        const char *start = pos;
        size_t token_len = 0;
        while (pos < sentence_end && *pos != '\0' && isalpha((unsigned char)*pos)) {
            pos++;
            token_len++;
            if (token_len > 255) {
                break;
            }
        }

        if (token_len == word_len) {
            int match = 1;
            size_t i;
            for (i = 0; i < word_len; i++) {
                if (tolower((unsigned char)start[i]) != tolower((unsigned char)word[i])) {
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
    sentence[sizeof(sentence) - 1] = '\0';
    size_t sentence_input_len = strnlen(sentence, sizeof(sentence));
    if (sentence_input_len > 0 && sentence[sentence_input_len - 1] == '\n') {
        sentence[sentence_input_len - 1] = '\0';
    } else if (sentence_input_len >= sizeof(sentence) - 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
            if (c == EOF) {
                clearerr(stdin);
                break;
            }
        }
    }

    printf("Enter a word to search: ");
    if (fgets(word, sizeof(word), stdin) == NULL) {
        fprintf(stderr, "Error reading word.\n");
        return 1;
    }
    word[sizeof(word) - 1] = '\0';
    size_t word_input_len = strnlen(word, sizeof(word));
    if (word_input_len > 0 && word[word_input_len - 1] == '\n') {
        word[word_input_len - 1] = '\0';
    } else if (word_input_len >= sizeof(word) - 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
            if (c == EOF) {
                clearerr(stdin);
                break;
            }
        }
    }

    if (is_word_present(sentence, word)) {
        printf("The word \"%s\" is present in the sentence.\n", word);
    } else {
        printf("The word \"%s\" is not present in the sentence.\n", word);
    }

    return 0;
}
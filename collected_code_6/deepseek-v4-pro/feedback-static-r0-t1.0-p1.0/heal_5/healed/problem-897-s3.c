#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SENTENCE_SIZE 1024
#define WORD_SIZE 256

int is_word_present(const char *sentence, const char *word) {
    if (sentence == NULL || word == NULL || *sentence == '\0' || *word == '\0') {
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
            int match = 1;
            for (size_t i = 0; i < word_len; i++) {
                if (tolower((unsigned char)start[i]) != tolower((unsigned char)word[i])) {
                    match = 0;
                    break;
                }
            }
            if (match) {
                return 1;
            }
        }
    }

    return 0;
}

int main(void) {
    char sentence[SENTENCE_SIZE] = {0};
    char word[WORD_SIZE] = {0};

    printf("Enter a sentence: ");
    if (fgets(sentence, sizeof(sentence), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }

    size_t len = 0;
    for (size_t i = 0; i < sizeof(sentence) && sentence[i] != '\0'; i++) {
        len = i + 1;
    }

    if (len > 0 && sentence[len - 1] == '\n') {
        sentence[len - 1] = '\0';
        len--;
    } else if (len == sizeof(sentence)) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }

    printf("Enter a word to search: ");
    if (fgets(word, sizeof(word), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }

    size_t word_len = 0;
    for (size_t i = 0; i < sizeof(word) && word[i] != '\0'; i++) {
        word_len = i + 1;
    }

    if (word_len > 0 && word[word_len - 1] == '\n') {
        word[word_len - 1] = '\0';
        word_len--;
    } else if (word_len == sizeof(word)) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }

    if (is_word_present(sentence, word)) {
        printf("The word \"%s\" is present in the sentence.\n", word);
    } else {
        printf("The word \"%s\" is not present in the sentence.\n", word);
    }

    return 0;
}
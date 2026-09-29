#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>
#include <stdbool.h>

bool is_word_present(const char *sentence, const char *word) {
    if (sentence == NULL || word == NULL || *sentence == '\0' || *word == '\0') {
        return false;
    }

    size_t word_len = strlen(word);
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
        if (token_len == word_len && strncasecmp(start, word, word_len) == 0) {
            return true;
        }
    }

    return false;
}

int main(void) {
    char sentence[1024];
    char word[256];

    printf("Enter a sentence: ");
    if (fgets(sentence, sizeof(sentence), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }
    sentence[strcspn(sentence, "\n")] = '\0';

    printf("Enter a word to search: ");
    if (fgets(word, sizeof(word), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }
    word[strcspn(word, "\n")] = '\0';

    if (is_word_present(sentence, word)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}
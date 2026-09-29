#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char sentence[1024];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[256];

    printf("Enter a sentence: ");
    if (fgets(sentence, sizeof(sentence), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }

    size_t len = 0;
    while (len < sizeof(sentence) && sentence[len] != '\0') {
        if (sentence[len] == '\n') {
            sentence[len] = '\0';
            break;
        }
        len++;
    }
    if (len == sizeof(sentence)) {
        sentence[sizeof(sentence) - 1] = '\0';
    }

    printf("Enter a word to search: ");
    if (fgets(word, sizeof(word), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }

    len = 0;
    while (len < sizeof(word) && word[len] != '\0') {
        if (word[len] == '\n') {
            word[len] = '\0';
            break;
        }
        len++;
    }
    if (len == sizeof(word)) {
        word[sizeof(word) - 1] = '\0';
    }

    if (is_word_present(sentence, word)) {
        printf("The word \"%s\" is present in the sentence.\n", word);
    } else {
        printf("The word \"%s\" is not present in the sentence.\n", word);
    }

    return 0;
}
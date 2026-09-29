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
    enum { SENTENCE_SIZE = 1024, WORD_SIZE = 256 };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char sentence[SENTENCE_SIZE];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[WORD_SIZE];

    printf("Enter a sentence: ");
    if (fgets(sentence, (int)sizeof(sentence), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(sentence);
    if (len > 0 && sentence[len - 1] == '\n') {
        sentence[len - 1] = '\0';
    } else if (len == sizeof(sentence) - 1) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
    }

    printf("Enter a word to search: ");
    if (fgets(word, (int)sizeof(word), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(word);
    if (len > 0 && word[len - 1] == '\n') {
        word[len - 1] = '\0';
    } else if (len == sizeof(word) - 1) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
    }

    if (is_word_present(sentence, word)) {
        printf("The word \"%s\" is present in the sentence.\n", word);
    } else {
        printf("The word \"%s\" is not present in the sentence.\n", word);
    }

    return 0;
}
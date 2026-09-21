#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define SENTENCE_MAX 256
#define WORD_MAX 64

int is_word_present(const char *sentence, const char *word);

int is_word_present(const char *sentence, const char *word)
{
    size_t word_len;
    size_t i;

    if (sentence == NULL || word == NULL) {
        return 0;
    }

    word_len = strnlen(word, WORD_MAX);
    if (word_len == 0U || word_len >= WORD_MAX) {
        return 0;
    }

    i = 0U;
    while (i < SENTENCE_MAX && sentence[i] != '\0') {
        while (i < SENTENCE_MAX && sentence[i] != '\0' &&
               !isalnum((unsigned char)sentence[i])) {
            i++;
        }
        if (i >= SENTENCE_MAX || sentence[i] == '\0') {
            break;
        }

        size_t start = i;
        while (i < SENTENCE_MAX && sentence[i] != '\0' &&
               isalnum((unsigned char)sentence[i])) {
            i++;
        }
        size_t token_len = i - start;

        if (token_len == word_len &&
            strncmp(&sentence[start], word, word_len) == 0) {
            return 1;
        }
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char sentence[SENTENCE_MAX];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[WORD_MAX];

    memset(sentence, 0, sizeof(sentence));
    memset(word, 0, sizeof(word));

    if (fgets(sentence, (int)sizeof(sentence), stdin) == NULL) {
        fprintf(stderr, "Error reading sentence.\n");
        return EXIT_FAILURE;
    }
    sentence[sizeof(sentence) - 1U] = '\0';
    sentence[strcspn(sentence, "\n")] = '\0';

    if (fgets(word, (int)sizeof(word), stdin) == NULL) {
        fprintf(stderr, "Error reading word.\n");
        return EXIT_FAILURE;
    }
    word[sizeof(word) - 1U] = '\0';
    word[strcspn(word, "\n")] = '\0';

    if (is_word_present(sentence, word) == 1) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return EXIT_SUCCESS;
}
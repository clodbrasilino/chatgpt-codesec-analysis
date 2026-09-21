#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int is_word_present(const char *sentence, const char *word);

int is_word_present(const char *sentence, const char *word)
{
    size_t word_len;
    size_t i;

    if (sentence == NULL || word == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    word_len = strlen(word);
    if (word_len == 0U) {
        return 0;
    }

    i = 0U;
    while (sentence[i] != '\0') {
        while (sentence[i] != '\0' && !isalnum((unsigned char)sentence[i])) {
            i++;
        }
        if (sentence[i] == '\0') {
            break;
        }

        size_t start = i;
        while (sentence[i] != '\0' && isalnum((unsigned char)sentence[i])) {
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
    char sentence[256];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[64];

    printf("Enter a sentence: ");
    if (fgets(sentence, sizeof(sentence), stdin) == NULL) {
        fprintf(stderr, "Error reading sentence.\n");
        return EXIT_FAILURE;
    }
    sentence[strcspn(sentence, "\n")] = '\0';

    printf("Enter a word to search: ");
    if (fgets(word, sizeof(word), stdin) == NULL) {
        fprintf(stderr, "Error reading word.\n");
        return EXIT_FAILURE;
    }
    word[strcspn(word, "\n")] = '\0';

    if (is_word_present(sentence, word) == 1) {
        printf("The word \"%s\" is present in the sentence.\n", word);
    } else {
        printf("The word \"%s\" is not present in the sentence.\n", word);
    }

    return EXIT_SUCCESS;
}
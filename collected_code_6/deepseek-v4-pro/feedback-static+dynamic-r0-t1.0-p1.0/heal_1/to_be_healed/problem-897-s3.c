#include <stdio.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected False, got <no output>
  *  test case 0 failed: expected True, got <no output>
  *  test case 1 failed: expected False, got <no output>
  */

int is_word_present(const char *sentence, const char *word) {
    if (sentence == NULL || word == NULL || *sentence == '\0' || *word == '\0') {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
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
            return 1;
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
    sentence[strcspn(sentence, "\n")] = '\0';

    printf("Enter a word to search: ");
    if (fgets(word, sizeof(word), stdin) == NULL) {
        printf("Error reading input.\n");
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
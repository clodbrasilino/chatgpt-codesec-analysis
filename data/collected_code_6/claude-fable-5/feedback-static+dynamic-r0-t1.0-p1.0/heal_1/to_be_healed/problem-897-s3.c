#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LEN 1024

int is_word_present(const char *sentence, const char *word)
{
    size_t word_len;
    const char *p;

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

    p = sentence;
    while (*p != '\0') {
        while (*p != '\0' && !isalnum((unsigned char)*p)) {
            p++;
        }
        if (*p == '\0') {
            break;
        }
        const char *start = p;
        while (*p != '\0' && isalnum((unsigned char)*p)) {
            p++;
        }
        size_t token_len = (size_t)(p - start);
        if (token_len == word_len && strncmp(start, word, word_len) == 0) {
            return 1;
        }
    }
    return 0;
}

static void strip_newline(char *s)
{
    size_t len;

    if (s == NULL) {
        return;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(s);
    if (len > 0U && s[len - 1U] == '\n') {
        s[len - 1U] = '\0';
    }
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char sentence[MAX_LEN];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_LEN];

    printf("Enter a sentence: ");
    if (fgets(sentence, sizeof(sentence), stdin) == NULL) {
        fprintf(stderr, "Error reading sentence.\n");
        return EXIT_FAILURE;
    }
    strip_newline(sentence);

    printf("Enter a word: ");
    if (fgets(word, sizeof(word), stdin) == NULL) {
        fprintf(stderr, "Error reading word.\n");
        return EXIT_FAILURE;
    }
    strip_newline(word);

    if (is_word_present(sentence, word) == 1) {
        printf("The word \"%s\" is present in the sentence.\n", word);
    } else {
        printf("The word \"%s\" is not present in the sentence.\n", word);
    }

    return EXIT_SUCCESS;
}
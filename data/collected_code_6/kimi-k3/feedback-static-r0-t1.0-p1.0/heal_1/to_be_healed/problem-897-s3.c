#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isWordPresent(const char *sentence, const char *word) {
    if (sentence == NULL || word == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t wordLen = strlen(word);
    if (wordLen == 0) {
        return 0;
    }

    const char *current = sentence;
    while ((current = strstr(current, word)) != NULL) {
        if ((current == sentence || !isalnum((unsigned char)current[-1])) &&
            !isalnum((unsigned char)current[wordLen])) {
            return 1;
        }
        current++;
    }

    return 0;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char sentence[256];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[256];

    printf("Enter a sentence: ");
    if (fgets(sentence, sizeof(sentence), stdin) == NULL) {
        fprintf(stderr, "Error reading sentence\n");
        return 1;
    }

    printf("Enter a word to search: ");
    if (fgets(word, sizeof(word), stdin) == NULL) {
        fprintf(stderr, "Error reading word\n");
        return 1;
    }

    sentence[strcspn(sentence, "\n")] = '\0';
    word[strcspn(word, "\n")] = '\0';

    if (isWordPresent(sentence, word)) {
        printf("The word is present in the sentence.\n");
    } else {
        printf("The word is not present in the sentence.\n");
    }

    return 0;
}
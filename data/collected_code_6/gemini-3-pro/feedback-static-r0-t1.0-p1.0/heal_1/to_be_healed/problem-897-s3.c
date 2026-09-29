#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

bool isWordPresent(const char *sentence, const char *word) {
    if (sentence == NULL || word == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t wordLen = strlen(word);
    if (wordLen == 0) {
        return false;
    }

    const char *current = sentence;
    while ((current = strstr(current, word)) != NULL) {
        bool startBoundary = (current == sentence || isspace((unsigned char)*(current - 1)) || ispunct((unsigned char)*(current - 1)));
        
        const char *end = current + wordLen;
        bool endBoundary = (*end == '\0' || isspace((unsigned char)*end) || ispunct((unsigned char)*end));

        if (startBoundary && endBoundary) {
            return true;
        }
        current++;
    }

    return false;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char sentence[256];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[64];

    if (fgets(sentence, sizeof(sentence), stdin) == NULL) {
        return 1;
    }

    if (fgets(word, sizeof(word), stdin) == NULL) {
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(sentence);
    if (len > 0 && sentence[len - 1] == '\n') {
        sentence[len - 1] = '\0';
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(word);
    if (len > 0 && word[len - 1] == '\n') {
        word[len - 1] = '\0';
    }

    if (isWordPresent(sentence, word)) {
        printf("Present\n");
    } else {
        printf("Not Present\n");
    }

    return 0;
}
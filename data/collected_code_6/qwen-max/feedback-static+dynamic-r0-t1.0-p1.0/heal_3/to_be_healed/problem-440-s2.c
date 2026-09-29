#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

bool isAdverb(const char *word) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(word);
    if (len < 4) return false;
    return (strcmp(word + len - 4, "ly") == 0);
}

void findAdverbs(const char *sentence, char **adverbs, int *positions, int *count) {
    const char *delimiters = " ,.!?;:";
    const char *token;
    const char *currentPos = sentence;
    char *context = NULL;

    token = strtok_r((char *)sentence, delimiters, &context);
    while (token != NULL) {
        if (isAdverb(token)) {
            adverbs[*count] = strdup(token);
            positions[*count] = currentPos - sentence;
            (*count)++;
        }
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        currentPos += strlen(token) + strspn(currentPos, delimiters);
        token = strtok_r(NULL, delimiters, &context);
    }
}

int main() {
    const char *sentence = "He quickly and quietly walked away from the scene.";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char *adverbs[100];
    int positions[100];
    int count = 0;

    findAdverbs(sentence, adverbs, positions, &count);

    for (int i = 0; i < count; i++) {
        printf("Adverb: %s, Position: %d\n", adverbs[i], positions[i]);
        free(adverbs[i]);
    }

    return 0;
}
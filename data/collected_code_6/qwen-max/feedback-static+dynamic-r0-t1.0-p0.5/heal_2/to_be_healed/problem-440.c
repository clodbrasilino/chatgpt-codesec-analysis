#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_SENTENCE_LENGTH 1024
#define MAX_ADVERBS 100

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[50];
    int start;
    int end;
} Adverb;

int is_adverb(const char *word) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(word);
    if (len > 3 && strncmp(word + len - 4, "ly", 2) == 0) {
        return 1;
    }
    return 0;
}

int find_adverbs(const char *sentence, Adverb *adverbs, int *count) {
    const char *delimiters = " ,.!?;:";
    char *copy = strdup(sentence);
    if (copy == NULL) {
        return -1;
    }

    char *token;
    int index = 0;

    token = strtok(copy, delimiters);
    while (token != NULL && index < MAX_ADVERBS) {
        if (is_adverb(token)) {
            adverbs[index].start = token - copy;
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            adverbs[index].end = adverbs[index].start + (int)strlen(token) - 1;
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(adverbs[index].word, token, sizeof(adverbs[index].word) - 1);
            adverbs[index].word[sizeof(adverbs[index].word) - 1] = '\0';
            index++;
        }
        token = strtok(NULL, delimiters);
    }

    free(copy);
    *count = index;
    return 0;
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char sentence[MAX_SENTENCE_LENGTH];
    Adverb adverbs[MAX_ADVERBS];
    int count = 0;

    printf("Enter a sentence: ");
    if (fgets(sentence, sizeof(sentence), stdin) == NULL) {
        return 1;
    }

    sentence[strcspn(sentence, "\n")] = '\0';

    if (find_adverbs(sentence, adverbs, &count) != 0) {
        fprintf(stderr, "Error processing sentence.\n");
        return 1;
    }

    for (int i = 0; i < count; i++) {
        printf("Adverb: %s, Start: %d, End: %d\n", adverbs[i].word, adverbs[i].start, adverbs[i].end);
    }

    return 0;
}
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SENTENCE_LENGTH 1024
#define MAX_ADVERBS 100

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[51];
    int start;
    int end;
} Adverb;

int is_adverb(const char *word, size_t len) {
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
        size_t len = strnlen(token, INT_MAX);
        if (is_adverb(token, len)) {
            adverbs[index].start = token - copy;
            adverbs[index].end = adverbs[index].start + (int)len - 1;
            snprintf(adverbs[index].word, sizeof(adverbs[index].word), "%.*s", (int)len, token);
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
    char sentence[MAX_SENTENCE_LENGTH] = {0};
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
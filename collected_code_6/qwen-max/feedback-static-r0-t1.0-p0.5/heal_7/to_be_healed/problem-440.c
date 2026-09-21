#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_SENTENCE_LENGTH 1024
#define MAX_ADVERBS 100

typedef struct {
    char *word;
    int start;
    int end;
} Adverb;

int is_adverb(const char *word, size_t len) {
    return len > 3 && !strncmp(word + len - 4, "ly", 2);
}

int find_adverbs(const char *sentence, Adverb *adverbs, int *count) {
    const char *delimiters = " ,.!?;:";
    char *copy = strdup(sentence);
    if (!copy) return -1;
    *count = 0;

    char *token = strtok(copy, delimiters);
    while (token != NULL && *count < MAX_ADVERBS) {
        size_t len = strnlen(token, MAX_SENTENCE_LENGTH);
        if (is_adverb(token, len)) {
            adverbs[*count].start = token - copy;
            adverbs[*count].end = adverbs[*count].start + (int)len - 1;
            adverbs[*count].word = strndup(token, len);
            (*count)++;
        }
        token = strtok(NULL, delimiters);
    }

    free(copy);
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
    if (!fgets(sentence, sizeof(sentence), stdin)) {
        return 1;
    }

    sentence[strcspn(sentence, "\n")] = '\0';

    if (find_adverbs(sentence, adverbs, &count) != 0) {
        return 1;
    }

    for (int i = 0; i < count; i++) {
        printf("Adverb: %s, Start: %d, End: %d\n", adverbs[i].word, adverbs[i].start, adverbs[i].end);
        free(adverbs[i].word);
    }

    return 0;
}
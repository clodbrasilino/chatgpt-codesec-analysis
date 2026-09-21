#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ADVERBS 100
#define MAX_WORD_LENGTH 50

typedef struct {
    char word[MAX_WORD_LENGTH + 1];
    int start;
    int end;
} AdverbInfo;

int is_adverb(const char *word, size_t len) {
    if (len < 3 || word[len - 2] != 'l' || word[len - 1] != 'y') return 0;
    return 1;
}

int find_adverbs(const char *sentence, AdverbInfo *adverbs, int *count) {
    const char *delimiters = " ,.!?;:()[]{}\"'";
    char *token;
    char *copy = strdup(sentence);
    if (!copy) return -1;

    *count = 0;
    token = strtok(copy, delimiters);
    while (token && *count < MAX_ADVERBS) {
        size_t len = strnlen(token, MAX_WORD_LENGTH + 1);
        if (len > 0 && len <= MAX_WORD_LENGTH && is_adverb(token, len)) {
            adverbs[*count].start = (int)(token - copy) + (int)(copy - sentence);
            adverbs[*count].end = adverbs[*count].start + (int)len - 1;
            snprintf(adverbs[*count].word, sizeof(adverbs[*count].word), "%.*s", (int)len, token);
            (*count)++;
        }
        token = strtok(NULL, delimiters);
    }

    free(copy);
    return 0;
}

int main() {
    char sentence[1000];
    int count = 0;

    printf("Enter a sentence: ");
    if (fgets(sentence, sizeof(sentence), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }
    sentence[strcspn(sentence, "\n")] = 0;

    AdverbInfo adverbs[MAX_ADVERBS];
    if (find_adverbs(sentence, adverbs, &count) != 0) {
        printf("Error finding adverbs.\n");
        return 1;
    }

    for (int i = 0; i < count; i++) {
        printf("Adverb: %s, Start: %d, End: %d\n", adverbs[i].word, adverbs[i].start, adverbs[i].end);
    }

    return 0;
}
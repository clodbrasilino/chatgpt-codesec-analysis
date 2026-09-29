#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_ADVERBS 100
#define MAX_WORD_LENGTH 50

typedef struct {
    char word[MAX_WORD_LENGTH];
    int start;
    int end;
} AdverbInfo;

int is_adverb(const char *word, size_t len) {
    return len >= 3 && word[len - 2] == 'l' && word[len - 1] == 'y';
}

int find_adverbs(const char *sentence, AdverbInfo *adverbs, int *count) {
    const char *delimiters = " ,.!?;:";
    char *copy = strdup(sentence);
    if (!copy) return -1;

    *count = 0;
    char *token = strtok(copy, delimiters);
    while (token) {
        size_t tok_len = strnlen(token, MAX_WORD_LENGTH);
        if (is_adverb(token, tok_len)) {
            adverbs[*count].start = token - copy + (copy - sentence);
            adverbs[*count].end = adverbs[*count].start + tok_len - 1;
            snprintf(adverbs[*count].word, sizeof(adverbs[*count].word), "%.*s", (int)tok_len, token);
            (*count)++;
            if (*count >= MAX_ADVERBS) break;
        }
        token = strtok(NULL, delimiters);
    }

    free(copy);
    return 0;
}

int main() {
    const char *sentence = "He quickly and quietly walked away from the scene.";
    AdverbInfo adverbs[MAX_ADVERBS];
    int count = 0;

    if (find_adverbs(sentence, adverbs, &count) == 0) {
        for (int i = 0; i < count; i++) {
            printf("Adverb: %s, Start: %d, End: %d\n", adverbs[i].word, adverbs[i].start, adverbs[i].end);
        }
    } else {
        printf("Error finding adverbs.\n");
    }

    return 0;
}
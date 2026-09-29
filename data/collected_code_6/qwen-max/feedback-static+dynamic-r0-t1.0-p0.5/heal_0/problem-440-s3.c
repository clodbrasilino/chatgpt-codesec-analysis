#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_ADVERBS 100
#define MAX_SENTENCE_LENGTH 256

typedef struct {
    char word[MAX_SENTENCE_LENGTH];
    int start;
    int end;
} Adverb;

int is_adverb(const char *word) {
    if (strlen(word) < 3) return 0;
    if (word[strlen(word) - 2] == 'l' && word[strlen(word) - 1] == 'y') return 1;
    return 0;
}

int find_adverbs(const char *sentence, Adverb *adverbs, int *count) {
    const char *delimiters = " ,.!?;:()[]{}\"'";
    char *token;
    char *copy = strdup(sentence);
    if (!copy) return -1;

    *count = 0;
    token = strtok(copy, delimiters);
    while (token) {
        if (is_adverb(token)) {
            adverbs[*count].start = token - copy + (copy - sentence);
            adverbs[*count].end = adverbs[*count].start + strlen(token) - 1;
            strncpy(adverbs[*count].word, token, sizeof(adverbs[*count].word));
            (*count)++;
        }
        token = strtok(NULL, delimiters);
    }

    free(copy);
    return 0;
}

int main() {
    char sentence[MAX_SENTENCE_LENGTH];
    Adverb adverbs[MAX_ADVERBS];
    int count = 0;

    printf("Enter a sentence: ");
    if (fgets(sentence, sizeof(sentence), stdin) == NULL) return 1;

    if (find_adverbs(sentence, adverbs, &count) != 0) return 1;

    for (int i = 0; i < count; i++) {
        printf("Adverb: %s, Start: %d, End: %d\n", adverbs[i].word, adverbs[i].start, adverbs[i].end);
    }

    return 0;
}
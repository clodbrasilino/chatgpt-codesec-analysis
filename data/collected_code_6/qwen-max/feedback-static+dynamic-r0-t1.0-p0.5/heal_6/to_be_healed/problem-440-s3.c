#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_ADVERBS 100
#define MAX_SENTENCE_LENGTH 256

typedef struct {
    char *word;
    int start;
    int end;
} Adverb;

int is_adverb(const char *word, size_t len) {
    if (len < 3) return 0;
    if (word[len - 2] == 'l' && word[len - 1] == 'y') return 1;
    return 0;
}

int find_adverbs(const char *sentence, Adverb *adverbs, int *count) {
    const char *delimiters = " ,.!?;:()[]{}\"'";
    char *copy = strdup(sentence);
    if (!copy) return -1;

    *count = 0;
    char *token = strtok(copy, delimiters);
    while (token) {
        size_t len = strnlen(token, MAX_SENTENCE_LENGTH);
        if (is_adverb(token, len)) {
            adverbs[*count].start = token - copy + (copy - sentence);
            adverbs[*count].end = adverbs[*count].start + len - 1;
            adverbs[*count].word = malloc(len + 1);
            if (!adverbs[*count].word) {
                free(copy);
                return -1;
            }
            snprintf(adverbs[*count].word, len + 1, "%.*s", (int)len, token);
            (*count)++;
        }
        token = strtok(NULL, delimiters);
    }

    free(copy);
    return 0;
}

int main() {
    char *sentence = malloc(MAX_SENTENCE_LENGTH);
    if (!sentence) return 1;

    Adverb adverbs[MAX_ADVERBS];
    int count = 0;

    printf("Enter a sentence: ");
    /* Possible weaknesses found:
     *  Memory leak: sentence [memleak]
     */
    if (fgets(sentence, MAX_SENTENCE_LENGTH, stdin) == NULL) return 1;

    sentence[strcspn(sentence, "\n")] = 0;

    if (find_adverbs(sentence, adverbs, &count) != 0) return 1;

    for (int i = 0; i < count; i++) {
        printf("Adverb: %s, Start: %d, End: %d\n", adverbs[i].word, adverbs[i].start, adverbs[i].end);
        free(adverbs[i].word);
    }

    free(sentence);
    return 0;
}
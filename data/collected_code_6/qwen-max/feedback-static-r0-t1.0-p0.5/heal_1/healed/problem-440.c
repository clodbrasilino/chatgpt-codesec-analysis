#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_SENTENCE_LENGTH 1024
#define MAX_ADVERBS 100

typedef struct {
    char word[50];
    int start;
    int end;
} Adverb;

int is_adverb(const char *word, size_t len) {
    return len > 3 && !strcmp(word + len - 4, "ly");
}

int find_adverbs(const char *sentence, Adverb *adverbs, int *count) {
    const char *delimiters = " ,.!?;:";
    char *token;
    char *copy = strdup(sentence);
    if (!copy) return -1;
    int index = 0;

    token = strtok(copy, delimiters);
    while (token != NULL && index < MAX_ADVERBS) {
        size_t len = strlen(token);
        if (is_adverb(token, len)) {
            adverbs[index].start = token - copy;
            adverbs[index].end = adverbs[index].start + len - 1;
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
    char sentence[MAX_SENTENCE_LENGTH];
    Adverb adverbs[MAX_ADVERBS];
    int count = 0;

    printf("Enter a sentence: ");
    if (fgets(sentence, sizeof(sentence), stdin) == NULL) {
        return 1;
    }

    sentence[strcspn(sentence, "\n")] = '\0';

    if (find_adverbs(sentence, adverbs, &count) != 0) {
        return 1;
    }

    for (int i = 0; i < count; i++) {
        printf("Adverb: %s, Start: %d, End: %d\n", adverbs[i].word, adverbs[i].start, adverbs[i].end);
    }

    return 0;
}
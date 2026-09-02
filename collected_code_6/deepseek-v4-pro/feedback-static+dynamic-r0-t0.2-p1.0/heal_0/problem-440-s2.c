#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 100
#define MAX_WORD_LEN 50

typedef struct {
    char word[MAX_WORD_LEN];
    int position;
} AdverbInfo;

int is_adverb(const char *word) {
    size_t len = strlen(word);
    if (len < 3) return 0;
    return strcmp(word + len - 2, "ly") == 0;
}

int find_adverbs(const char *sentence, AdverbInfo *adverbs, int max_adverbs) {
    if (sentence == NULL || adverbs == NULL || max_adverbs <= 0) {
        return -1;
    }

    int count = 0;
    int pos = 0;
    size_t len = strlen(sentence);
    char *buffer = (char *)malloc(len + 1);
    if (buffer == NULL) {
        return -1;
    }
    strcpy(buffer, sentence);

    char *token = strtok(buffer, " ,.!?;:\"()[]{}");
    while (token != NULL && count < max_adverbs) {
        if (is_adverb(token)) {
            strncpy(adverbs[count].word, token, MAX_WORD_LEN - 1);
            adverbs[count].word[MAX_WORD_LEN - 1] = '\0';
            adverbs[count].position = pos;
            count++;
        }
        pos++;
        token = strtok(NULL, " ,.!?;:\"()[]{}");
    }

    free(buffer);
    return count;
}

int main(void) {
    char sentence[1024];
    AdverbInfo adverbs[MAX_WORDS];

    printf("Enter a sentence: ");
    if (fgets(sentence, sizeof(sentence), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    sentence[strcspn(sentence, "\n")] = '\0';

    int num_adverbs = find_adverbs(sentence, adverbs, MAX_WORDS);
    if (num_adverbs < 0) {
        fprintf(stderr, "Error processing sentence\n");
        return 1;
    }

    printf("Adverbs found: %d\n", num_adverbs);
    for (int i = 0; i < num_adverbs; i++) {
        printf("Position %d: %s\n", adverbs[i].position, adverbs[i].word);
    }

    return 0;
}
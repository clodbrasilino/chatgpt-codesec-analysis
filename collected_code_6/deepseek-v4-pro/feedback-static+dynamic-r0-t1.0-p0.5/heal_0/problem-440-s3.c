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

    char *copy = malloc(strlen(sentence) + 1);
    if (copy == NULL) {
        return -1;
    }
    strcpy(copy, sentence);

    int count = 0;
    int position = 0;
    char *token = strtok(copy, " \t\n\r.,;:!?\"'()[]{}");

    while (token != NULL && count < max_adverbs) {
        size_t len = strlen(token);
        if (len > 0) {
            char lower[MAX_WORD_LEN];
            size_t i;
            for (i = 0; i < len && i < MAX_WORD_LEN - 1; i++) {
                lower[i] = tolower((unsigned char)token[i]);
            }
            lower[i] = '\0';

            if (is_adverb(lower)) {
                strncpy(adverbs[count].word, token, MAX_WORD_LEN - 1);
                adverbs[count].word[MAX_WORD_LEN - 1] = '\0';
                adverbs[count].position = position;
                count++;
            }
        }
        position++;
        token = strtok(NULL, " \t\n\r.,;:!?\"'()[]{}");
    }

    free(copy);
    return count;
}

int main(void) {
    const char *sentence = "The quick brown fox jumps quickly and silently over the lazy dog.";
    AdverbInfo adverbs[MAX_WORDS];
    int num_adverbs;
    int i;

    num_adverbs = find_adverbs(sentence, adverbs, MAX_WORDS);

    if (num_adverbs < 0) {
        fprintf(stderr, "Error processing sentence\n");
        return EXIT_FAILURE;
    }

    printf("Sentence: %s\n", sentence);
    printf("Found %d adverb(s):\n", num_adverbs);

    for (i = 0; i < num_adverbs; i++) {
        printf("  Word: %s, Position: %d\n", adverbs[i].word, adverbs[i].position);
    }

    return EXIT_SUCCESS;
}
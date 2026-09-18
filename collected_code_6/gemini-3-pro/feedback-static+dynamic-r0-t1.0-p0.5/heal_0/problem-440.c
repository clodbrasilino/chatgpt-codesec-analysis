#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *word;
    int position;
} AdverbInfo;

int is_adverb(const char *word) {
    size_t len = strlen(word);
    if (len > 2 && strcmp(word + len - 2, "ly") == 0) {
        return 1;
    }
    return 0;
}

AdverbInfo* find_adverbs(const char *sentence, int *count) {
    if (!sentence || !count) {
        return NULL;
    }

    char *sentence_copy = strdup(sentence);
    if (!sentence_copy) {
        return NULL;
    }

    AdverbInfo *adverbs = NULL;
    int capacity = 0;
    *count = 0;

    char *token = strtok(sentence_copy, " \t\n\r.,;:!?()[]{}");
    int position = 0;

    while (token != NULL) {
        if (is_adverb(token)) {
            if (*count >= capacity) {
                capacity = capacity == 0 ? 4 : capacity * 2;
                AdverbInfo *temp = realloc(adverbs, capacity * sizeof(AdverbInfo));
                if (!temp) {
                    for (int i = 0; i < *count; i++) {
                        free(adverbs[i].word);
                    }
                    free(adverbs);
                    free(sentence_copy);
                    return NULL;
                }
                adverbs = temp;
            }
            adverbs[*count].word = strdup(token);
            if (!adverbs[*count].word) {
                for (int i = 0; i < *count; i++) {
                    free(adverbs[i].word);
                }
                free(adverbs);
                free(sentence_copy);
                return NULL;
            }
            adverbs[*count].position = position;
            (*count)++;
        }
        token = strtok(NULL, " \t\n\r.,;:!?()[]{}");
        position++;
    }

    free(sentence_copy);
    return adverbs;
}

int main(void) {
    const char *sentence = "He quickly ran to the store and quietly bought some milk.";
    int count = 0;

    AdverbInfo *adverbs = find_adverbs(sentence, &count);

    if (adverbs) {
        for (int i = 0; i < count; i++) {
            printf("Adverb: %s, Position: %d\n", adverbs[i].word, adverbs[i].position);
            free(adverbs[i].word);
        }
        free(adverbs);
    } else {
        printf("No adverbs found or memory allocation failed.\n");
    }

    return 0;
}
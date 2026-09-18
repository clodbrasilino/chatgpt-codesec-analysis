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
    if (len > 2 && word[len - 2] == 'l' && word[len - 1] == 'y') {
        return 1;
    }
    return 0;
}

AdverbInfo* find_adverbs(const char *sentence, int *count) {
    if (!sentence || !count) {
        return NULL;
    }

    *count = 0;
    char *sentence_copy = strdup(sentence);
    if (!sentence_copy) {
        return NULL;
    }

    int capacity = 10;
    AdverbInfo *adverbs = malloc(capacity * sizeof(AdverbInfo));
    if (!adverbs) {
        free(sentence_copy);
        return NULL;
    }

    char *token = strtok(sentence_copy, " \t\n.,;:!?");
    int position = 0;

    while (token != NULL) {
        if (is_adverb(token)) {
            if (*count >= capacity) {
                capacity *= 2;
                AdverbInfo *temp = realloc(adverbs, capacity * sizeof(AdverbInfo));
                if (!temp) {
                    for (int i = 0; i < *count; i++) {
                        free(adverbs[i].word);
                    }
                    free(adverbs);
                    free(sentence_copy);
                    *count = 0;
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
                *count = 0;
                return NULL;
            }
            adverbs[*count].position = position;
            (*count)++;
        }
        position++;
        token = strtok(NULL, " \t\n.,;:!?");
    }

    free(sentence_copy);
    return adverbs;
}

int main(void) {
    const char *sentence = "He quickly ran to the store and happily bought some groceries.";
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
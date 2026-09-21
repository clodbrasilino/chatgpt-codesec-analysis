#if defined(__linux__) || defined(__APPLE__)
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 2048

typedef struct {
    char *word;
    int position;
} AdverbInfo;

typedef struct {
    AdverbInfo *adverbs;
    int count;
} AdverbList;

int is_adverb(const char *word) {
    size_t len = strnlen(word, MAX_WORD_LEN);
    if (len > 2 && len < MAX_WORD_LEN && strncmp(word + len - 2, "ly", 2) == 0) {
        return 1;
    }
    return 0;
}

AdverbList find_adverbs(const char *sentence) {
    AdverbList list = {NULL, 0};
    if (!sentence) return list;

    char *sentence_copy = strdup(sentence);
    if (!sentence_copy) return list;

    int capacity = 10;
    list.adverbs = malloc(capacity * sizeof(AdverbInfo));
    if (!list.adverbs) {
        free(sentence_copy);
        return list;
    }

    const char *delimiters = " \t\n\r.,;:!?\"'()[]{}";
    char *saveptr = NULL;
    char *token = strtok_r(sentence_copy, delimiters, &saveptr);
    int position = 0;

    while (token != NULL) {
        if (is_adverb(token)) {
            if (list.count >= capacity) {
                capacity *= 2;
                AdverbInfo *temp = realloc(list.adverbs, capacity * sizeof(AdverbInfo));
                if (!temp) {
                    for (int i = 0; i < list.count; i++) {
                        free(list.adverbs[i].word);
                    }
                    free(list.adverbs);
                    free(sentence_copy);
                    list.adverbs = NULL;
                    list.count = 0;
                    return list;
                }
                list.adverbs = temp;
            }
            list.adverbs[list.count].word = strdup(token);
            if (list.adverbs[list.count].word) {
                list.adverbs[list.count].position = position;
                list.count++;
            }
        }
        position++;
        token = strtok_r(NULL, delimiters, &saveptr);
    }

    free(sentence_copy);
    return list;
}

void free_adverb_list(AdverbList *list) {
    if (list && list->adverbs) {
        for (int i = 0; i < list->count; i++) {
            free(list->adverbs[i].word);
        }
        free(list->adverbs);
        list->adverbs = NULL;
        list->count = 0;
    }
}

int main(void) {
    const char *sentence = "He quickly ran to the store and happily bought some groceries.";
    
    AdverbList result = find_adverbs(sentence);
    
    for (int i = 0; i < result.count; i++) {
        printf("Adverb: %s, Position: %d\n", result.adverbs[i].word, result.adverbs[i].position);
    }
    
    free_adverb_list(&result);
    
    return 0;
}
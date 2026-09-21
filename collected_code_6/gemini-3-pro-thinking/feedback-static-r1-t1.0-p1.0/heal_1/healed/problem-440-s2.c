#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *word;
    size_t position;
} AdverbInfo;

typedef struct {
    AdverbInfo *adverbs;
    size_t count;
    size_t capacity;
} AdverbList;

int init_adverb_list(AdverbList *list) {
    if (!list) {
        return 0;
    }
    list->count = 0;
    list->capacity = 10;
    list->adverbs = malloc(list->capacity * sizeof(AdverbInfo));
    if (!list->adverbs) {
        return 0;
    }
    return 1;
}

void free_adverb_list(AdverbList *list) {
    if (!list) {
        return;
    }
    if (list->adverbs) {
        for (size_t i = 0; i < list->count; i++) {
            free(list->adverbs[i].word);
        }
        free(list->adverbs);
        list->adverbs = NULL;
    }
    list->count = 0;
    list->capacity = 0;
}

int add_adverb(AdverbList *list, const char *start, size_t length, size_t position) {
    if (!list || !start) {
        return 0;
    }
    if (list->count >= list->capacity) {
        size_t new_cap = list->capacity * 2;
        AdverbInfo *new_arr = realloc(list->adverbs, new_cap * sizeof(AdverbInfo));
        if (!new_arr) {
            return 0;
        }
        list->adverbs = new_arr;
        list->capacity = new_cap;
    }
    
    char *new_word = malloc(length + 1);
    if (!new_word) {
        return 0;
    }
    
    for (size_t i = 0; i < length; i++) {
        new_word[i] = start[i];
    }
    new_word[length] = '\0';
    
    list->adverbs[list->count].word = new_word;
    list->adverbs[list->count].position = position;
    list->count++;
    return 1;
}

int find_adverbs(const char *sentence, AdverbList *list) {
    if (!sentence || !list) {
        return 0;
    }

    size_t i = 0;
    size_t word_start = 0;
    int in_word = 0;

    while (1) {
        if (isalpha((unsigned char)sentence[i])) {
            if (!in_word) {
                word_start = i;
                in_word = 1;
            }
        } else {
            if (in_word) {
                size_t length = i - word_start;
                if (length >= 2) {
                    if (tolower((unsigned char)sentence[i - 2]) == 'l' &&
                        tolower((unsigned char)sentence[i - 1]) == 'y') {
                        if (!add_adverb(list, &sentence[word_start], length, word_start)) {
                            return 0;
                        }
                    }
                }
                in_word = 0;
            }
        }
        if (sentence[i] == '\0') {
            break;
        }
        i++;
    }
    return 1;
}

int main(void) {
    const char *text = "The cat quickly and silently jumped over the fence, landing perfectly.";
    AdverbList list;

    if (!init_adverb_list(&list)) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    if (find_adverbs(text, &list)) {
        for (size_t i = 0; i < list.count; i++) {
            printf("Adverb: \"%s\", Position: %zu\n", list.adverbs[i].word, list.adverbs[i].position);
        }
    } else {
        fprintf(stderr, "Error occurred while processing the sentence.\n");
        free_adverb_list(&list);
        return EXIT_FAILURE;
    }

    free_adverb_list(&list);
    return EXIT_SUCCESS;
}
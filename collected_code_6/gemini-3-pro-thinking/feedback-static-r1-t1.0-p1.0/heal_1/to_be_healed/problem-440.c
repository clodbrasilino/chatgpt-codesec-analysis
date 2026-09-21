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

void free_adverb_list(AdverbList *list) {
    if (!list) {
        return;
    }
    if (list->adverbs) {
        for (size_t i = 0; i < list->count; i++) {
            free(list->adverbs[i].word);
        }
        free(list->adverbs);
    }
    free(list);
}

AdverbList *find_adverbs(const char *sentence) {
    if (!sentence) {
        return NULL;
    }

    AdverbList *list = malloc(sizeof(AdverbList));
    if (!list) {
        return NULL;
    }

    list->count = 0;
    list->capacity = 10;
    list->adverbs = malloc(list->capacity * sizeof(AdverbInfo));
    
    if (!list->adverbs) {
        free(list);
        return NULL;
    }

    size_t i = 0;
    while (sentence[i] != '\0') {
        if (isalpha((unsigned char)sentence[i])) {
            size_t start = i;
            while (sentence[i] != '\0' && isalpha((unsigned char)sentence[i])) {
                i++;
            }
            size_t len = i - start;
            
            if (len >= 2) {
                if (tolower((unsigned char)sentence[i - 2]) == 'l' &&
                    tolower((unsigned char)sentence[i - 1]) == 'y') {
                    
                    if (list->count >= list->capacity) {
                        size_t new_capacity = list->capacity * 2;
                        AdverbInfo *temp = realloc(list->adverbs, new_capacity * sizeof(AdverbInfo));
                        if (!temp) {
                            free_adverb_list(list);
                            return NULL;
                        }
                        list->adverbs = temp;
                        list->capacity = new_capacity;
                    }

                    list->adverbs[list->count].word = malloc(len + 1);
                    if (!list->adverbs[list->count].word) {
                        free_adverb_list(list);
                        return NULL;
                    }

                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(list->adverbs[list->count].word, &sentence[start], len);
                    list->adverbs[list->count].word[len] = '\0';
                    list->adverbs[list->count].position = start;
                    list->count++;
                }
            }
        } else {
            i++;
        }
    }

    return list;
}

int main(void) {
    const char *sentence = "The fox quickly jumped over the dog and silently ran away.";
    AdverbList *adverbs = find_adverbs(sentence);

    if (!adverbs) {
        fprintf(stderr, "Failed to process the sentence.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < adverbs->count; i++) {
        printf("Adverb: %s, Position: %zu\n", adverbs->adverbs[i].word, adverbs->adverbs[i].position);
    }

    free_adverb_list(adverbs);
    return EXIT_SUCCESS;
}
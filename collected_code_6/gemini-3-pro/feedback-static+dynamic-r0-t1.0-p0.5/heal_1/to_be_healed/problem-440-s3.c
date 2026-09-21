#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *word;
    int position;
} AdverbInfo;

int is_adverb(const char *word) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
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

    *count = 0;
    int current_pos = 0;
    char *token = strtok(sentence_copy, " \t\n\r.,;:!?");

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
            
            const char *word_in_orig = strstr(sentence + current_pos, token);
            if (word_in_orig) {
                adverbs[*count].position = (int)(word_in_orig - sentence);
                /* Possible weaknesses found:
                 * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                 */
                current_pos = adverbs[*count].position + strlen(token);
            } else {
                adverbs[*count].position = -1;
            }
            
            (*count)++;
        }
        token = strtok(NULL, " \t\n\r.,;:!?");
    }

    free(sentence_copy);
    return adverbs;
}

void free_adverbs(AdverbInfo *adverbs, int count) {
    if (adverbs) {
        for (int i = 0; i < count; i++) {
            free(adverbs[i].word);
        }
        free(adverbs);
    }
}

int main(void) {
    const char *sentence = "He quickly ran to the store and happily bought some groceries.";
    int count = 0;
    
    AdverbInfo *adverbs = find_adverbs(sentence, &count);
    
    if (adverbs) {
        for (int i = 0; i < count; i++) {
            printf("Adverb: %s, Position: %d\n", adverbs[i].word, adverbs[i].position);
        }
        free_adverbs(adverbs, count);
    } else {
        printf("No adverbs found or memory allocation failed.\n");
    }
    
    return 0;
}
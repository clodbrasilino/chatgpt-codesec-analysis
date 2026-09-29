#if defined(__linux__) || defined(__APPLE__)
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *word;
    int position;
} AdverbInfo;

int is_adverb(const char *word) {
    if (!word) {
        return 0;
    }
    
    size_t len = 0;
    size_t max_len = 4096;

    while (len < max_len && word[len] != '\0') {
        len++;
    }
    
    if (len > 2 && len < max_len && word[len - 2] == 'l' && word[len - 1] == 'y') {
        return 1;
    }
    return 0;
}

AdverbInfo* find_adverbs(const char *sentence, int *count) {
    if (!sentence || !count) {
        return NULL;
    }

    *count = 0;
    
    size_t sent_len = 0;

    /* Possible weaknesses found:
     *  Assuming that condition 'sent_len<65536' is not redundant
     *  Array index out of bounds
     *  Either the condition 'sent_len<65536' is redundant or the array 'sentence[63]' is accessed at index 65535, which is out of bounds. [arrayIndexOutOfBoundsCond]
     */
    while (sent_len < 65536 && sentence[sent_len] != '\0') {
        sent_len++;
    }
    
    char *sentence_copy = malloc(sent_len + 1);
    if (!sentence_copy) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(sentence_copy, sentence, sent_len);
    sentence_copy[sent_len] = '\0';

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
            
            size_t tok_len = 0;
            while (token[tok_len] != '\0') tok_len++;
            
            adverbs[*count].word = malloc(tok_len + 1);
            if (!adverbs[*count].word) {
                for (int i = 0; i < *count; i++) {
                    free(adverbs[i].word);
                }
                free(adverbs);
                free(sentence_copy);
                *count = 0;
                return NULL;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(adverbs[*count].word, token, tok_len);
            adverbs[*count].word[tok_len] = '\0';
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
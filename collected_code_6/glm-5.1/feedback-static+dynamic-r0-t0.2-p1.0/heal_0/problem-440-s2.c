#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int position;
    char *word;
} Adverb;

int is_adverb(const char *word) {
    size_t len = strlen(word);
    if (len < 3) {
        return 0;
    }
    if (word[len - 2] == 'l' && word[len - 1] == 'y') {
        return 1;
    }
    return 0;
}

Adverb *find_adverbs(const char *sentence, int *count) {
    Adverb *results = NULL;
    *count = 0;
    size_t len = strlen(sentence);
    
    char *buffer = (char *)malloc(len + 1);
    if (buffer == NULL) {
        return NULL;
    }
    memcpy(buffer, sentence, len + 1);

    int capacity = 0;
    char *token = strtok(buffer, " \t\n\r.,;:!?\"'");
    
    while (token != NULL) {
        if (is_adverb(token)) {
            if (*count >= capacity) {
                capacity = capacity == 0 ? 4 : capacity * 2;
                Adverb *temp = (Adverb *)realloc(results, capacity * sizeof(Adverb));
                if (temp == NULL) {
                    for (int i = 0; i < *count; i++) {
                        free(results[i].word);
                    }
                    free(results);
                    free(buffer);
                    *count = 0;
                    return NULL;
                }
                results = temp;
            }
            
            size_t word_len = strlen(token);
            results[*count].word = (char *)malloc(word_len + 1);
            if (results[*count].word == NULL) {
                for (int i = 0; i < *count; i++) {
                    free(results[i].word);
                }
                free(results);
                free(buffer);
                *count = 0;
                return NULL;
            }
            memcpy(results[*count].word, token, word_len + 1);
            
            results[*count].position = (int)(token - buffer);
            (*count)++;
        }
        token = strtok(NULL, " \t\n\r.,;:!?\"'");
    }
    
    free(buffer);
    return results;
}

int main() {
    const char *sentence = "She quickly ran to the store and happily bought the brightly colored balloons.";
    int count = 0;
    
    Adverb *adverbs = find_adverbs(sentence, &count);
    
    if (adverbs != NULL) {
        for (int i = 0; i < count; i++) {
            printf("Adverb: %s, Position: %d\n", adverbs[i].word, adverbs[i].position);
            free(adverbs[i].word);
        }
        free(adverbs);
    }
    
    return 0;
}
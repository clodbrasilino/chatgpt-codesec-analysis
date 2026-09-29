#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int position;
    char *word;
} Adverb;

int is_adverb(const char *word, size_t len) {
    if (len > 2) {
        if (tolower((unsigned char)word[len - 2]) == 'l' && tolower((unsigned char)word[len - 1]) == 'y') {
            return 1;
        }
    }
    return 0;
}

Adverb *find_adverbs(const char *sentence, size_t sentence_len, int *count) {
    Adverb *results = NULL;
    *count = 0;
    
    /* Possible weaknesses found:
     *  Assuming that condition 'sentence_len==0' is not redundant
     */
    if (sentence == NULL || sentence_len == 0) {
        return NULL;
    }

    char *buffer = (char *)malloc(sentence_len + 1);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (buffer == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  Condition 'sentence_len>0' is always true
     *  Condition 'sentence_len>0' is always true [knownConditionTrueFalse]
     */
    if (sentence_len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(buffer, sentence, sentence_len + 1);
        buffer[sentence_len] = '\0';
    }

    int capacity = 10;
    results = (Adverb *)malloc(capacity * sizeof(Adverb));
    if (results == NULL) {
        free(buffer);
        return NULL;
    }

    int pos = 0;
    char *token = strtok(buffer, " ,.;!?\"'-");
    
    while (token != NULL) {
        char *token_start = token;
        size_t token_len = 0;
        /* Possible weaknesses found:
         *  Array index 'token_len' is used before limits check. [arrayIndexThenCheck]
         */
        while (token_start[token_len] != '\0' && token_len < sentence_len) {
            token_len++;
        }

        if (token_len > 0 && is_adverb(token, token_len)) {
            if (*count >= capacity) {
                capacity *= 2;
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

            results[*count].word = (char *)malloc(token_len + 1);
            if (results[*count].word == NULL) {
                for (int i = 0; i < *count; i++) {
                    free(results[i].word);
                }
                free(results);
                free(buffer);
                *count = 0;
                return NULL;
            }
            
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(results[*count].word, token, token_len);
            results[*count].word[token_len] = '\0';
            results[*count].position = pos;
            (*count)++;
        }
        
        pos += token_len + 1;
        token = strtok(NULL, " ,.;!?\"'-");
    }

    free(buffer);
    return results;
}

void free_adverbs(Adverb *adverbs, int count) {
    if (adverbs != NULL) {
        for (int i = 0; i < count; i++) {
            free(adverbs[i].word);
        }
        free(adverbs);
    }
}

int main() {
    const char *sentence = "She quickly ran to the store and happily bought the newly released book.";
    size_t sentence_len = 0;
    /* Possible weaknesses found:
     *  Array index 'sentence_len' is used before limits check. [arrayIndexThenCheck]
     */
    while (sentence[sentence_len] != '\0' && sentence_len < 1024) {
        sentence_len++;
    }

    int count = 0;
    
    Adverb *adverbs = find_adverbs(sentence, sentence_len, &count);
    
    if (adverbs != NULL) {
        for (int i = 0; i < count; i++) {
            printf("Adverb: %s, Position: %d\n", adverbs[i].word, adverbs[i].position);
        }
        free_adverbs(adverbs, count);
    }
    
    return 0;
}
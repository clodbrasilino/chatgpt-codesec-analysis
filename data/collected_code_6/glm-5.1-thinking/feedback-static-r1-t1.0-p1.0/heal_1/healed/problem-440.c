#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *word;
    size_t position;
} AdverbInfo;

AdverbInfo* find_adverbs(const char *sentence, size_t *count) {
    if (!sentence || !count) {
        return NULL;
    }

    *count = 0;
    size_t capacity = 4;
    AdverbInfo *results = malloc(capacity * sizeof(AdverbInfo));
    if (!results) {
        return NULL;
    }

    size_t i = 0;
    while (sentence[i] != '\0') {
        if (isalpha((unsigned char)sentence[i])) {
            size_t start = i;
            while (sentence[i] != '\0' && isalpha((unsigned char)sentence[i])) {
                i++;
            }
            size_t word_len = i - start;

            if (word_len >= 2 && 
                tolower((unsigned char)sentence[i - 2]) == 'l' && 
                tolower((unsigned char)sentence[i - 1]) == 'y') {
                
                if (*count >= capacity) {
                    capacity *= 2;
                    AdverbInfo *temp = realloc(results, capacity * sizeof(AdverbInfo));
                    if (!temp) {
                        for (size_t j = 0; j < *count; j++) {
                            free(results[j].word);
                        }
                        free(results);
                        return NULL;
                    }
                    results = temp;
                }

                results[*count].word = malloc(word_len + 1);
                if (!results[*count].word) {
                    for (size_t j = 0; j < *count; j++) {
                        free(results[j].word);
                    }
                    free(results);
                    return NULL;
                }

                snprintf(results[*count].word, word_len + 1, "%.*s", (int)word_len, &sentence[start]);
                results[*count].position = start;
                (*count)++;
            }
        } else {
            i++;
        }
    }

    if (*count == 0) {
        free(results);
        return NULL;
    }

    AdverbInfo *final_results = realloc(results, *count * sizeof(AdverbInfo));
    return final_results ? final_results : results;
}

int main(void) {
    const char *sentence = "He quickly ran away and suddenly stopped silently.";
    size_t count = 0;
    AdverbInfo *adverbs = find_adverbs(sentence, &count);

    if (adverbs) {
        for (size_t i = 0; i < count; i++) {
            printf("Adverb: %s, Position: %zu\n", adverbs[i].word, adverbs[i].position);
            free(adverbs[i].word);
        }
        free(adverbs);
    } else {
        printf("No adverbs found or memory allocation failed.\n");
    }

    return 0;
}
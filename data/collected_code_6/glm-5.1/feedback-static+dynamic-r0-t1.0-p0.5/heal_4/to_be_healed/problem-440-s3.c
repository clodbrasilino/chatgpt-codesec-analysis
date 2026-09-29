#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *word;
    size_t position;
} Adverb;

int is_adverb(const char *word, size_t len) {
    if (len < 3) {
        return 0;
    }
    if (word[len - 2] == 'l' && word[len - 1] == 'y') {
        return 1;
    }
    return 0;
}

Adverb *find_adverbs(const char *sentence, size_t sen_len, size_t *out_count) {
    Adverb *results = NULL;
    size_t count = 0;
    size_t capacity = 0;
    size_t i = 0;

    while (i < sen_len) {
        while (i < sen_len && !isalpha((unsigned char)sentence[i])) {
            i++;
        }
        if (i >= sen_len) {
            break;
        }

        size_t start = i;
        while (i < sen_len && isalpha((unsigned char)sentence[i])) {
            i++;
        }
        size_t word_len = i - start;

        char *word = (char *)malloc(word_len + 1);
        if (!word) {
            for (size_t j = 0; j < count; j++) {
                free(results[j].word);
            }
            free(results);
            *out_count = 0;
            return NULL;
        }

        if (word_len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(word, sentence + start, word_len + 1);
        }
        word[word_len] = '\0';

        if (is_adverb(word, word_len)) {
            if (count >= capacity) {
                size_t new_capacity = capacity == 0 ? 4 : capacity * 2;
                Adverb *new_results = (Adverb *)realloc(results, new_capacity * sizeof(Adverb));
                if (!new_results) {
                    free(word);
                    for (size_t j = 0; j < count; j++) {
                        free(results[j].word);
                    }
                    free(results);
                    *out_count = 0;
                    return NULL;
                }
                results = new_results;
                capacity = new_capacity;
            }
            results[count].word = word;
            results[count].position = start;
            count++;
        } else {
            free(word);
        }
    }

    *out_count = count;
    return results;
}

int main(void) {
    const char *sentence = "He quickly ran to the slowly moving car and loudly honked the horn.";
    size_t count = 0;
    size_t sen_len = strnlen(sentence, 1024);
    Adverb *adverbs = find_adverbs(sentence, sen_len, &count);

    if (adverbs != NULL) {
        for (size_t i = 0; i < count; i++) {
            printf("Adverb: %s, Position: %zu\n", adverbs[i].word, adverbs[i].position);
            free(adverbs[i].word);
        }
        free(adverbs);
    }

    return 0;
}
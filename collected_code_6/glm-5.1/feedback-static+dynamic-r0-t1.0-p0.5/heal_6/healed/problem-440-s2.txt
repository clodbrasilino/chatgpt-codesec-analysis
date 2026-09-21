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

Adverb *find_adverbs(const char *sentence, size_t *out_count) {
    Adverb *results = NULL;
    size_t count = 0;
    size_t capacity = 0;
    const char *p = sentence;

    while (*p) {
        while (*p && !isalpha((unsigned char)*p)) {
            p++;
        }
        if (!*p) {
            break;
        }

        size_t start_pos = (size_t)(p - sentence);
        const char *word_start = p;

        while (*p && isalpha((unsigned char)*p)) {
            p++;
        }
        size_t word_len = (size_t)(p - word_start);

        char *word = (char *)malloc(word_len + 1);
        if (word == NULL) {
            for (size_t j = 0; j < count; j++) {
                free(results[j].word);
            }
            free(results);
            *out_count = 0;
            return NULL;
        }

        if (word_len > 0) {
            memcpy(word, word_start, word_len);
        }
        word[word_len] = '\0';

        if (is_adverb(word, word_len)) {
            if (count >= capacity) {
                size_t new_capacity = (capacity == 0) ? 4 : capacity * 2;
                Adverb *new_results = (Adverb *)realloc(results, new_capacity * sizeof(Adverb));
                if (new_results == NULL) {
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
            results[count].position = start_pos;
            count++;
        } else {
            free(word);
        }
    }

    *out_count = count;
    return results;
}

int main(void) {
    const char *sentence = "He quickly ran to the slowly moving car and happily drove away.";
    size_t count = 0;

    Adverb *adverbs = find_adverbs(sentence, &count);

    if (adverbs != NULL) {
        for (size_t i = 0; i < count; i++) {
            printf("Adverb: %s, Position: %zu\n", adverbs[i].word, adverbs[i].position);
            free(adverbs[i].word);
        }
        free(adverbs);
    }

    return 0;
}
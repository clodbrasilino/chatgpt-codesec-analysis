#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *word;
    size_t position;
} Adverb;

Adverb *find_adverbs(const char *sentence, size_t *count) {
    if (sentence == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;
    size_t capacity = 10;
    Adverb *results = malloc(capacity * sizeof(Adverb));
    if (results == NULL) {
        return NULL;
    }

    const char *suffix = "ly";
    size_t suffix_len = strlen(suffix);
    const char *ptr = sentence;
    size_t index = 0;

    while (*ptr) {
        while (*ptr && isspace((unsigned char)*ptr)) {
            ptr++;
            index++;
        }

        if (!*ptr) {
            break;
        }

        const char *start = ptr;
        size_t start_index = index;

        while (*ptr && !isspace((unsigned char)*ptr)) {
            ptr++;
            index++;
        }

        size_t word_len = ptr - start;

        if (word_len > suffix_len) {
            const char *word_end = start + word_len;
            if (strncmp(word_end - suffix_len, suffix, suffix_len) == 0) {
                if (*count >= capacity) {
                    capacity *= 2;
                    Adverb *temp = realloc(results, capacity * sizeof(Adverb));
                    if (temp == NULL) {
                        for (size_t i = 0; i < *count; i++) {
                            free(results[i].word);
                        }
                        free(results);
                        return NULL;
                    }
                    results = temp;
                }

                results[*count].word = malloc(word_len + 1);
                if (results[*count].word == NULL) {
                    for (size_t i = 0; i < *count; i++) {
                        free(results[i].word);
                    }
                    free(results);
                    return NULL;
                }

                memcpy(results[*count].word, start, word_len);
                results[*count].word[word_len] = '\0';
                results[*count].position = start_index;
                (*count)++;
            }
        }
    }

    return results;
}

int main(void) {
    const char *sentence = "He quickly ran to the slowly moving car and hastily drove away.";
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
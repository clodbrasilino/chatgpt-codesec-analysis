#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

typedef struct {
    char *word;
    int count;
} WordCount;

char *str_dup(const char *s) {
    if (s == NULL) return NULL;
    size_t len = strnlen(s, SIZE_MAX);
    if (len == SIZE_MAX) return NULL;
    char *d = malloc(len + 1);
    if (d) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(d, s, len + 1);
    }
    return d;
}

void find_most_common(const char *text) {
    if (text == NULL) return;

    size_t capacity = 16;
    size_t size = 0;
    WordCount *counts = malloc(capacity * sizeof(WordCount));
    if (counts == NULL) return;

    const char *p = text;
    while (*p) {
        while (*p && !isalpha((unsigned char)*p)) p++;
        if (!*p) break;

        const char *start = p;
        while (*p && isalpha((unsigned char)*p)) p++;

        size_t len = (size_t)(p - start);
        char *word = malloc(len + 1);
        if (word == NULL) {
            for (size_t i = 0; i < size; i++) free(counts[i].word);
            free(counts);
            return;
        }
        if (len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(word, start, len);
        }
        word[len] = '\0';
        for (size_t i = 0; word[i]; i++) word[i] = tolower((unsigned char)word[i]);

        int found = 0;
        for (size_t i = 0; i < size; i++) {
            if (strcmp(counts[i].word, word) == 0) {
                counts[i].count++;
                found = 1;
                free(word);
                break;
            }
        }

        if (!found) {
            if (size >= capacity) {
                size_t new_cap = capacity * 2;
                if (new_cap < capacity) {
                    free(word);
                    for (size_t i = 0; i < size; i++) free(counts[i].word);
                    free(counts);
                    return;
                }
                WordCount *new_counts = realloc(counts, new_cap * sizeof(WordCount));
                if (new_counts == NULL) {
                    free(word);
                    for (size_t i = 0; i < size; i++) free(counts[i].word);
                    free(counts);
                    return;
                }
                counts = new_counts;
                capacity = new_cap;
            }
            counts[size].word = word;
            counts[size].count = 1;
            size++;
        }
    }

    if (size == 0) {
        free(counts);
        return;
    }

    int max_count = 0;
    for (size_t i = 0; i < size; i++) {
        if (counts[i].count > max_count) {
            max_count = counts[i].count;
        }
    }

    printf("Most common elements (count: %d):\n", max_count);
    for (size_t i = 0; i < size; i++) {
        if (counts[i].count == max_count) {
            printf("%s\n", counts[i].word);
        }
    }

    for (size_t i = 0; i < size; i++) free(counts[i].word);
    free(counts);
}

int main(void) {
    const char *text = "Hello world! Hello C developers. C is a great language, hello!";
    find_most_common(text);
    return 0;
}
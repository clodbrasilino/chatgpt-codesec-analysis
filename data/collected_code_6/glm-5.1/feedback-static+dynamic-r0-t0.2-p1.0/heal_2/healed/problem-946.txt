#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

typedef struct {
    char *word;
    int count;
} WordCount;

char *strdup_new(const char *s) {
    size_t len = strnlen(s, SIZE_MAX);
    if (len == SIZE_MAX) {
        return NULL;
    }
    char *d = malloc(len + 1);
    if (d) {
        memcpy(d, s, len + 1);
    }
    return d;
}

void find_most_common(const char *text) {
    if (text == NULL) {
        return;
    }

    size_t capacity = 16;
    size_t size = 0;
    WordCount *words = malloc(capacity * sizeof(WordCount));
    if (words == NULL) {
        return;
    }

    const char *p = text;
    while (*p) {
        while (*p && !isalpha((unsigned char)*p)) {
            p++;
        }
        if (!*p) {
            break;
        }

        const char *start = p;
        size_t len = 0;
        while (*p && isalpha((unsigned char)*p)) {
            len++;
            p++;
        }

        char *word = malloc(len + 1);
        if (word == NULL) {
            for (size_t i = 0; i < size; i++) {
                free(words[i].word);
            }
            free(words);
            return;
        }

        for (size_t i = 0; i < len; i++) {
            word[i] = tolower((unsigned char)start[i]);
        }
        word[len] = '\0';

        int found = 0;
        for (size_t i = 0; i < size; i++) {
            if (strcmp(words[i].word, word) == 0) {
                words[i].count++;
                found = 1;
                free(word);
                break;
            }
        }

        if (!found) {
            if (size >= capacity) {
                size_t new_capacity = capacity * 2;
                if (new_capacity < capacity || (new_capacity * sizeof(WordCount)) / sizeof(WordCount) != new_capacity) {
                    free(word);
                    for (size_t i = 0; i < size; i++) {
                        free(words[i].word);
                    }
                    free(words);
                    return;
                }
                WordCount *new_words = realloc(words, new_capacity * sizeof(WordCount));
                if (new_words == NULL) {
                    free(word);
                    for (size_t i = 0; i < size; i++) {
                        free(words[i].word);
                    }
                    free(words);
                    return;
                }
                words = new_words;
                capacity = new_capacity;
            }
            words[size].word = word;
            words[size].count = 1;
            size++;
        }
    }

    if (size == 0) {
        free(words);
        return;
    }

    int max_count = 0;
    for (size_t i = 0; i < size; i++) {
        if (words[i].count > max_count) {
            max_count = words[i].count;
        }
    }

    printf("Most common elements (count: %d):\n", max_count);
    for (size_t i = 0; i < size; i++) {
        if (words[i].count == max_count) {
            printf("%s\n", words[i].word);
        }
    }

    for (size_t i = 0; i < size; i++) {
        free(words[i].word);
    }
    free(words);
}

int main(void) {
    const char *text = "Hello world! This is a test. Hello again, this test is only a test.";
    find_most_common(text);
    return 0;
}
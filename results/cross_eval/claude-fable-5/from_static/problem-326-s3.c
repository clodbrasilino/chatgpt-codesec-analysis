#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_WORD_LEN 256

struct WordCount {
    char *word;
    size_t count;
};

static char *duplicate_string(const char *src, size_t len)
{
    char *dst;

    if (src == NULL || len >= SIZE_MAX) {
        return NULL;
    }

    dst = malloc(len + 1);
    if (dst == NULL) {
        return NULL;
    }

    memcpy(dst, src, len);
    dst[len] = '\0';
    return dst;
}

static int add_word(struct WordCount **words, size_t *size, size_t *capacity,
                    const char *word, size_t word_len)
{
    size_t i;

    if (words == NULL || size == NULL || capacity == NULL || word == NULL) {
        return -1;
    }

    if (word_len >= MAX_WORD_LEN) {
        return -1;
    }

    for (i = 0; i < *size; i++) {
        if (strncmp((*words)[i].word, word, word_len) == 0 &&
            (*words)[i].word[word_len] == '\0') {
            if ((*words)[i].count == SIZE_MAX) {
                return -1;
            }
            (*words)[i].count++;
            return 0;
        }
    }

    if (*size == *capacity) {
        size_t new_capacity = (*capacity == 0) ? 8 : (*capacity * 2);
        struct WordCount *tmp;

        if (new_capacity <= *capacity ||
            new_capacity > SIZE_MAX / sizeof(struct WordCount)) {
            return -1;
        }

        tmp = realloc(*words, new_capacity * sizeof(struct WordCount));
        if (tmp == NULL) {
            return -1;
        }
        *words = tmp;
        *capacity = new_capacity;
    }

    (*words)[*size].word = duplicate_string(word, word_len);
    if ((*words)[*size].word == NULL) {
        return -1;
    }

    (*words)[*size].count = 1;
    (*size)++;
    return 0;
}

static void free_words(struct WordCount *words, size_t size)
{
    size_t i;

    if (words == NULL) {
        return;
    }

    for (i = 0; i < size; i++) {
        free(words[i].word);
    }
    free(words);
}

char *most_frequent_word(const char **strings, size_t num_strings)
{
    struct WordCount *words = NULL;
    size_t size = 0;
    size_t capacity = 0;
    size_t i;
    size_t best_index = 0;
    size_t best_len;
    char *result = NULL;
    char buffer[MAX_WORD_LEN];

    if (strings == NULL || num_strings == 0) {
        return NULL;
    }

    for (i = 0; i < num_strings; i++) {
        const char *p = strings[i];
        if (p == NULL) {
            continue;
        }
        while (*p != '\0') {
            size_t len = 0;
            while (*p == ' ' || *p == '\t' || *p == '\n') {
                p++;
            }
            while (*p != '\0' && *p != ' ' && *p != '\t' && *p != '\n') {
                if (len < MAX_WORD_LEN - 1) {
                    buffer[len] = *p;
                    len++;
                }
                p++;
            }
            buffer[len] = '\0';
            if (len > 0) {
                if (add_word(&words, &size, &capacity, buffer, len) != 0) {
                    free_words(words, size);
                    return NULL;
                }
            }
        }
    }

    if (size == 0) {
        free_words(words, size);
        return NULL;
    }

    for (i = 1; i < size; i++) {
        if (words[i].count > words[best_index].count) {
            best_index = i;
        }
    }

    best_len = strnlen(words[best_index].word, MAX_WORD_LEN - 1);
    result = duplicate_string(words[best_index].word, best_len);

    free_words(words, size);
    return result;
}

int main(void)
{
    const char *strings[] = {
        "the quick brown fox",
        "the lazy dog and the cat",
        "quick quick fox"
    };
    size_t num_strings = sizeof(strings) / sizeof(strings[0]);
    char *word = most_frequent_word(strings, num_strings);

    if (word == NULL) {
        fprintf(stderr, "Failed to find most frequent word\n");
        return EXIT_FAILURE;
    }

    if (printf("Most frequent word: %s\n", word) < 0) {
        free(word);
        return EXIT_FAILURE;
    }

    free(word);
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 256

struct WordCount {
    char *word;
    size_t len;
    size_t count;
};

static int add_word(struct WordCount **words, size_t *size, size_t *capacity,
                    const char *word, size_t word_len)
{
    size_t i;

    for (i = 0; i < *size; i++) {
        if ((*words)[i].len == word_len &&
            memcmp((*words)[i].word, word, word_len) == 0) {
            (*words)[i].count++;
            return 0;
        }
    }

    if (*size == *capacity) {
        size_t new_capacity = (*capacity == 0) ? 8 : (*capacity * 2);
        struct WordCount *tmp;

        if (new_capacity > SIZE_MAX / sizeof(struct WordCount)) {
            return -1;
        }
        tmp = realloc(*words, new_capacity * sizeof(struct WordCount));
        if (tmp == NULL) {
            return -1;
        }
        *words = tmp;
        *capacity = new_capacity;
    }

    (*words)[*size].word = malloc(word_len + 1);
    if ((*words)[*size].word == NULL) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy((*words)[*size].word, word, word_len);
    (*words)[*size].word[word_len] = '\0';
    (*words)[*size].len = word_len;
    (*words)[*size].count = 1;
    (*size)++;
    return 0;
}

static void free_words(struct WordCount *words, size_t size)
{
    size_t i;

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
    char *result = NULL;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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
                if (len < sizeof(buffer) - 1) {
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

    result = malloc(words[best_index].len + 1);
    if (result != NULL) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result, words[best_index].word, words[best_index].len);
        result[words[best_index].len] = '\0';
    }

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
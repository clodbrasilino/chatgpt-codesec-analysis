#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

#define MAX_WORD_LEN 64

typedef struct WordCount {
    char *word;
    size_t count;
} WordCount;

static int compare_counts(const void *a, const void *b)
{
    const WordCount *wa = (const WordCount *)a;
    const WordCount *wb = (const WordCount *)b;

    if (wb->count > wa->count) {
        return 1;
    }
    if (wb->count < wa->count) {
        return -1;
    }
    return strcmp(wa->word, wb->word);
}

static WordCount *find_word(WordCount *words, size_t count, const char *word)
{
    size_t i;

    if (words == NULL || word == NULL) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        if (words[i].word != NULL && strcmp(words[i].word, word) == 0) {
            return &words[i];
        }
    }
    return NULL;
}

static char *duplicate_word(const char *word, size_t word_len)
{
    char *copy;

    if (word == NULL || word_len == 0 || word_len >= MAX_WORD_LEN) {
        return NULL;
    }

    if (strnlen(word, MAX_WORD_LEN) < word_len) {
        return NULL;
    }

    copy = malloc(word_len + 1);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, word, word_len);
    copy[word_len] = '\0';
    return copy;
}

static int add_word(WordCount **words, size_t *count, size_t *capacity, const char *word)
{
    WordCount *existing;
    WordCount *resized;
    char *copy;
    size_t word_len;

    if (words == NULL || count == NULL || capacity == NULL || word == NULL) {
        return -1;
    }

    word_len = strnlen(word, MAX_WORD_LEN);
    if (word_len == 0 || word_len >= MAX_WORD_LEN) {
        return -1;
    }

    existing = find_word(*words, *count, word);
    if (existing != NULL) {
        if (existing->count == SIZE_MAX) {
            return -1;
        }
        existing->count++;
        return 0;
    }

    if (*count >= *capacity) {
        size_t new_capacity;

        if (*capacity > SIZE_MAX / 2) {
            return -1;
        }
        new_capacity = (*capacity == 0) ? 16 : (*capacity * 2);
        if (new_capacity > SIZE_MAX / sizeof(WordCount)) {
            return -1;
        }
        resized = realloc(*words, new_capacity * sizeof(WordCount));
        if (resized == NULL) {
            return -1;
        }
        *words = resized;
        *capacity = new_capacity;
    }

    copy = duplicate_word(word, word_len);
    if (copy == NULL) {
        return -1;
    }

    (*words)[*count].word = copy;
    (*words)[*count].count = 1;
    (*count)++;
    return 0;
}

static void free_words(WordCount *words, size_t count)
{
    size_t i;

    if (words == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        free(words[i].word);
        words[i].word = NULL;
    }
    free(words);
}

static int count_words(const char *text, size_t text_len, WordCount **words, size_t *word_count)
{
    size_t capacity = 0;
    size_t i = 0;
    char buffer[MAX_WORD_LEN];

    if (words == NULL || word_count == NULL) {
        return -1;
    }

    *words = NULL;
    *word_count = 0;

    if (text == NULL) {
        return -1;
    }

    while (i < text_len && text[i] != '\0') {
        size_t j = 0;

        while (i < text_len && text[i] != '\0' && !isalpha((unsigned char)text[i])) {
            i++;
        }

        while (i < text_len && text[i] != '\0' && isalpha((unsigned char)text[i])) {
            if (j < sizeof(buffer) - 1) {
                buffer[j] = (char)tolower((unsigned char)text[i]);
                j++;
            }
            i++;
        }

        if (j > 0 && j < sizeof(buffer)) {
            buffer[j] = '\0';
            if (add_word(words, word_count, &capacity, buffer) != 0) {
                free_words(*words, *word_count);
                *words = NULL;
                *word_count = 0;
                return -1;
            }
        }
    }

    return 0;
}

static int print_top_words(const char *text, size_t text_len, size_t n)
{
    WordCount *words = NULL;
    size_t word_count = 0;
    size_t i;
    size_t limit;

    if (count_words(text, text_len, &words, &word_count) != 0) {
        fprintf(stderr, "Failed to process text\n");
        return -1;
    }

    if (word_count == 0) {
        printf("No words found.\n");
        free_words(words, word_count);
        return 0;
    }

    qsort(words, word_count, sizeof(WordCount), compare_counts);

    limit = (n < word_count) ? n : word_count;

    for (i = 0; i < limit; i++) {
        printf("%s: %zu\n", words[i].word, words[i].count);
    }

    free_words(words, word_count);
    return 0;
}

int main(void)
{
    static const char text[] = "The quick brown fox jumps over the lazy dog. "
                               "The dog barks and the fox runs. The quick fox "
                               "is quick and the dog is lazy.";
    size_t n = 5;

    printf("Top %zu most common words:\n", n);

    if (print_top_words(text, sizeof(text) - 1, n) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
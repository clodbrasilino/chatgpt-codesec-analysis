#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 64

typedef struct WordCount {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LEN];
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

    for (i = 0; i < count; i++) {
        if (strcmp(words[i].word, word) == 0) {
            return &words[i];
        }
    }
    return NULL;
}

static int add_word(WordCount **words, size_t *count, size_t *capacity, const char *word)
{
    WordCount *existing;
    WordCount *resized;

    existing = find_word(*words, *count, word);
    if (existing != NULL) {
        existing->count++;
        return 0;
    }

    if (*count >= *capacity) {
        size_t new_capacity = (*capacity == 0) ? 16 : (*capacity * 2);
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

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy((*words)[*count].word, word, MAX_WORD_LEN - 1);
    (*words)[*count].word[MAX_WORD_LEN - 1] = '\0';
    (*words)[*count].count = 1;
    (*count)++;
    return 0;
}

static int count_words(const char *text, WordCount **words, size_t *word_count)
{
    size_t capacity = 0;
    size_t i = 0;
    size_t len;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_WORD_LEN];

    *words = NULL;
    *word_count = 0;

    if (text == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(text);

    while (i < len) {
        size_t j = 0;

        while (i < len && !isalpha((unsigned char)text[i])) {
            i++;
        }

        while (i < len && isalpha((unsigned char)text[i])) {
            if (j < MAX_WORD_LEN - 1) {
                /* Possible weaknesses found:
                 *  Variable 'buffer[j]' is assigned a value that is never used. [unreadVariable]
                 */
                buffer[j] = (char)tolower((unsigned char)text[i]);
                j++;
            }
            i++;
        }

        if (j > 0) {
            buffer[j] = '\0';
            if (add_word(words, word_count, &capacity, buffer) != 0) {
                free(*words);
                *words = NULL;
                *word_count = 0;
                return -1;
            }
        }
    }

    return 0;
}

static int print_top_words(const char *text, size_t n)
{
    WordCount *words = NULL;
    size_t word_count = 0;
    size_t i;
    size_t limit;

    if (count_words(text, &words, &word_count) != 0) {
        fprintf(stderr, "Failed to process text\n");
        return -1;
    }

    if (word_count == 0) {
        printf("No words found.\n");
        free(words);
        return 0;
    }

    qsort(words, word_count, sizeof(WordCount), compare_counts);

    limit = (n < word_count) ? n : word_count;

    for (i = 0; i < limit; i++) {
        printf("%s: %zu\n", words[i].word, words[i].count);
    }

    free(words);
    return 0;
}

int main(void)
{
    const char *text = "The quick brown fox jumps over the lazy dog. "
                       "The dog barks and the fox runs. The quick fox "
                       "is quick and the dog is lazy.";
    size_t n = 5;

    printf("Top %zu most common words:\n", n);

    if (print_top_words(text, n) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
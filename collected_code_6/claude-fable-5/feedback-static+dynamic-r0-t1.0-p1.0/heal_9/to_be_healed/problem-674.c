#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_INPUT_LEN 1048576

typedef struct {
    char *text;
    size_t len;
} word_t;

char *remove_duplicate_words(const char *input);
static size_t bounded_len(const char *src, size_t max_len);
static int is_delim(char c);
static int word_seen(const word_t *words, size_t count, const char *word, size_t word_len);
static void free_words(word_t *words, size_t count);
static char *dup_word(const char *src, size_t word_len);

static size_t bounded_len(const char *src, size_t max_len)
{
    size_t n = 0;
    while (n < max_len && src[n] != '\0') {
        n++;
    }
    return n;
}

static int is_delim(char c)
{
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

static int word_seen(const word_t *words, size_t count, const char *word, size_t word_len)
{
    size_t i;
    for (i = 0; i < count; i++) {
        if (words[i].len == word_len && memcmp(words[i].text, word, word_len) == 0) {
            return 1;
        }
    }
    return 0;
}

static void free_words(word_t *words, size_t count)
{
    size_t i;
    if (words == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        free(words[i].text);
    }
    free(words);
}

static char *dup_word(const char *src, size_t word_len)
{
    char *dst;
    if (src == NULL || word_len == 0 || word_len >= MAX_INPUT_LEN) {
        return NULL;
    }
    dst = malloc(word_len + 1);
    if (dst == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dst, src, word_len);
    dst[word_len] = '\0';
    return dst;
}

char *remove_duplicate_words(const char *input)
{
    char *result;
    word_t *words;
    size_t count;
    size_t capacity;
    size_t len;
    size_t i;
    size_t pos;
    size_t offset;

    if (input == NULL) {
        return NULL;
    }

    len = bounded_len(input, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        return NULL;
    }

    capacity = 16;
    count = 0;
    words = malloc(capacity * sizeof(word_t));
    if (words == NULL) {
        return NULL;
    }

    pos = 0;
    while (pos < len) {
        size_t start;
        size_t word_len;

        while (pos < len && is_delim(input[pos])) {
            pos++;
        }
        if (pos >= len) {
            break;
        }
        start = pos;
        while (pos < len && !is_delim(input[pos])) {
            pos++;
        }
        word_len = pos - start;
        if (word_len == 0) {
            continue;
        }

        if (!word_seen(words, count, input + start, word_len)) {
            if (count == capacity) {
                size_t new_capacity;
                word_t *tmp;
                if (capacity > SIZE_MAX / 2 / sizeof(word_t)) {
                    free_words(words, count);
                    return NULL;
                }
                new_capacity = capacity * 2;
                tmp = realloc(words, new_capacity * sizeof(word_t));
                if (tmp == NULL) {
                    free_words(words, count);
                    return NULL;
                }
                words = tmp;
                capacity = new_capacity;
            }
            words[count].text = dup_word(input + start, word_len);
            if (words[count].text == NULL) {
                free_words(words, count);
                return NULL;
            }
            words[count].len = word_len;
            count++;
        }
    }

    result = malloc(len + 1);
    if (result == NULL) {
        free_words(words, count);
        return NULL;
    }

    offset = 0;
    result[0] = '\0';
    for (i = 0; i < count; i++) {
        size_t word_len = words[i].len;
        if (i > 0) {
            if (offset >= len) {
                free_words(words, count);
                free(result);
                return NULL;
            }
            result[offset] = ' ';
            offset++;
        }
        if (words[i].text == NULL || word_len > len - offset) {
            free_words(words, count);
            free(result);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + offset, words[i].text, word_len);
        offset += word_len;
    }
    result[offset] = '\0';

    free_words(words, count);
    return result;
}

int main(void)
{
    const char *text = "Python Exercises Practice Solution Exercises Practice";
    char *deduped;

    deduped = remove_duplicate_words(text);
    if (deduped == NULL) {
        fprintf(stderr, "Failed to process string\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", deduped);
    fflush(stdout);

    free(deduped);
    return EXIT_SUCCESS;
}
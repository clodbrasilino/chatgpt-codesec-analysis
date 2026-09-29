#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *remove_duplicate_words(const char *input);
static int word_seen(char **words, size_t count, const char *word);
static void free_words(char **words, size_t count);
static char *duplicate_string(const char *src, size_t src_len);

static int word_seen(char **words, size_t count, const char *word)
{
    size_t i;
    for (i = 0; i < count; i++) {
        if (strcmp(words[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

static void free_words(char **words, size_t count)
{
    size_t i;
    for (i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
}

static char *duplicate_string(const char *src, size_t src_len)
{
    char *dest;
    size_t dest_size;

    if (src == NULL || src_len == SIZE_MAX) {
        return NULL;
    }

    dest_size = src_len + 1;
    dest = malloc(dest_size);
    if (dest == NULL) {
        return NULL;
    }

    if (src_len > dest_size - 1) {
        free(dest);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dest, src, src_len);
    dest[src_len] = '\0';
    return dest;
}

char *remove_duplicate_words(const char *input)
{
    char *copy;
    char *result;
    char **words;
    char *token;
    char *saveptr;
    size_t count;
    size_t capacity;
    size_t len;
    size_t i;
    size_t offset;
    size_t result_size;

    if (input == NULL) {
        return NULL;
    }

    len = strnlen(input, SIZE_MAX - 1);

    copy = duplicate_string(input, len);
    if (copy == NULL) {
        return NULL;
    }

    capacity = 16;
    count = 0;
    words = malloc(capacity * sizeof(char *));
    if (words == NULL) {
        free(copy);
        return NULL;
    }

    token = strtok_r(copy, " \t\n", &saveptr);
    while (token != NULL) {
        if (!word_seen(words, count, token)) {
            size_t token_len;
            if (count == capacity) {
                size_t new_capacity;
                char **tmp;
                if (capacity > SIZE_MAX / 2 / sizeof(char *)) {
                    free_words(words, count);
                    free(copy);
                    return NULL;
                }
                new_capacity = capacity * 2;
                tmp = realloc(words, new_capacity * sizeof(char *));
                if (tmp == NULL) {
                    free_words(words, count);
                    free(copy);
                    return NULL;
                }
                words = tmp;
                capacity = new_capacity;
            }
            token_len = strnlen(token, len);
            words[count] = duplicate_string(token, token_len);
            if (words[count] == NULL) {
                free_words(words, count);
                free(copy);
                return NULL;
            }
            count++;
        }
        token = strtok_r(NULL, " \t\n", &saveptr);
    }

    free(copy);

    result_size = len + 1;
    result = malloc(result_size);
    if (result == NULL) {
        free_words(words, count);
        return NULL;
    }

    offset = 0;
    for (i = 0; i < count; i++) {
        size_t word_len = strnlen(words[i], len);
        if (i > 0) {
            if (offset >= len || offset >= result_size - 1) {
                free_words(words, count);
                free(result);
                return NULL;
            }
            result[offset] = ' ';
            offset++;
        }
        if (word_len > len - offset || offset + word_len > result_size - 1) {
            free_words(words, count);
            free(result);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + offset, words[i], word_len);
        offset += word_len;
    }
    result[offset] = '\0';

    free_words(words, count);
    return result;
}

int main(void)
{
    const char *text = "the quick brown fox the lazy dog quick brown";
    char *deduped;

    deduped = remove_duplicate_words(text);
    if (deduped == NULL) {
        fprintf(stderr, "Failed to process string\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", text);
    printf("Deduplicated: %s\n", deduped);

    free(deduped);
    return EXIT_SUCCESS;
}
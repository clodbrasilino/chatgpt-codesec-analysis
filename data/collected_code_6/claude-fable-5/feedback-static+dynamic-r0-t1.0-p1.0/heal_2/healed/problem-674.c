#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *remove_duplicate_words(const char *input);
static int word_seen(char **words, size_t count, const char *word);
static void free_words(char **words, size_t count);

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

    if (input == NULL) {
        return NULL;
    }

    len = strlen(input);
    copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }
    memcpy(copy, input, len);
    copy[len] = '\0';

    capacity = 16;
    count = 0;
    words = malloc(capacity * sizeof(char *));
    if (words == NULL) {
        free(copy);
        return NULL;
    }

    saveptr = NULL;
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
            token_len = strlen(token);
            words[count] = malloc(token_len + 1);
            if (words[count] == NULL) {
                free_words(words, count);
                free(copy);
                return NULL;
            }
            memcpy(words[count], token, token_len);
            words[count][token_len] = '\0';
            count++;
        }
        token = strtok_r(NULL, " \t\n", &saveptr);
    }

    free(copy);

    result = malloc(len + 1);
    if (result == NULL) {
        free_words(words, count);
        return NULL;
    }

    offset = 0;
    result[0] = '\0';
    for (i = 0; i < count; i++) {
        size_t word_len = strlen(words[i]);
        if (i > 0) {
            if (offset + 1 > len) {
                free_words(words, count);
                free(result);
                return NULL;
            }
            result[offset] = ' ';
            offset++;
        }
        if (offset + word_len > len) {
            free_words(words, count);
            free(result);
            return NULL;
        }
        memcpy(result + offset, words[i], word_len);
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

    printf("Original: %s\n", text);
    printf("Deduplicated: %s\n", deduped);

    free(deduped);
    return EXIT_SUCCESS;
}
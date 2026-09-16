#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static void free_word_array(char **words, size_t count)
{
    if (words == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
}

char *remove_duplicate_words(const char *input)
{
    if (input == NULL) {
        return NULL;
    }

    size_t capacity = 8;
    size_t count = 0;
    char **words = malloc(capacity * sizeof(*words));
    if (words == NULL) {
        return NULL;
    }

    const char *p = input;

    while (*p != '\0') {
        while (isspace((unsigned char)*p)) {
            p++;
        }
        if (*p == '\0') {
            break;
        }

        const char *start = p;
        while (*p != '\0' && !isspace((unsigned char)*p)) {
            p++;
        }
        size_t len = (size_t)(p - start);

        int duplicate = 0;
        for (size_t i = 0; i < count; i++) {
            if (strlen(words[i]) == len && strncmp(words[i], start, len) == 0) {
                duplicate = 1;
                break;
            }
        }
        if (duplicate) {
            continue;
        }

        char *word = malloc(len + 1);
        if (word == NULL) {
            free_word_array(words, count);
            return NULL;
        }
        memcpy(word, start, len);
        word[len] = '\0';

        if (count == capacity) {
            if (capacity > (size_t)-1 / 2) {
                free(word);
                free_word_array(words, count);
                return NULL;
            }
            size_t new_capacity = capacity * 2;
            char **new_words = realloc(words, new_capacity * sizeof(*words));
            if (new_words == NULL) {
                free(word);
                free_word_array(words, count);
                return NULL;
            }
            words = new_words;
            capacity = new_capacity;
        }

        words[count] = word;
        count++;
    }

    size_t result_len = 1;
    for (size_t i = 0; i < count; i++) {
        result_len += strlen(words[i]);
        if (i > 0) {
            result_len += 1;
        }
    }

    char *result = malloc(result_len);
    if (result == NULL) {
        free_word_array(words, count);
        return NULL;
    }

    size_t pos = 0;
    for (size_t i = 0; i < count; i++) {
        if (i > 0) {
            result[pos] = ' ';
            pos++;
        }
        size_t wlen = strlen(words[i]);
        memcpy(result + pos, words[i], wlen);
        pos += wlen;
    }
    result[pos] = '\0';

    free_word_array(words, count);
    return result;
}

int main(void)
{
    const char text[] = "apple banana apple cherry banana";
    char *result = remove_duplicate_words(text);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    printf("%s\n", result);
    free(result);
    return EXIT_SUCCESS;
}
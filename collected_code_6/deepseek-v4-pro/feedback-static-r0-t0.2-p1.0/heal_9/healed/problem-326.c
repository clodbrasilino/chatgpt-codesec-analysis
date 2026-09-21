#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 100

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordCount;

static size_t safe_str_copy(char *dest, const char *src, size_t dest_size) {
    if (dest == NULL || src == NULL || dest_size == 0) {
        if (dest != NULL && dest_size > 0) {
            dest[0] = '\0';
        }
        return 0;
    }

    size_t i;
    for (i = 0; i < dest_size - 1 && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return i;
}

static char *safe_strndup(const char *src, size_t max_len) {
    if (src == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (len < max_len && src[len] != '\0') {
        len++;
    }

    char *dest = (char *)malloc(len + 1);
    if (dest == NULL) {
        return NULL;
    }

    if (len > 0) {
        memcpy(dest, src, len);
    }
    dest[len] = '\0';
    return dest;
}

static int is_delimiter(char c, const char *delimiters) {
    while (*delimiters) {
        if (c == *delimiters) {
            return 1;
        }
        delimiters++;
    }
    return 0;
}

static char *safe_strtok(char *str, const char *delimiters, char **saveptr) {
    if (str == NULL && saveptr == NULL) {
        return NULL;
    }

    if (str != NULL) {
        *saveptr = str;
    }

    if (*saveptr == NULL || **saveptr == '\0') {
        return NULL;
    }

    while (**saveptr != '\0' && is_delimiter(**saveptr, delimiters)) {
        (*saveptr)++;
    }

    if (**saveptr == '\0') {
        return NULL;
    }

    char *token_start = *saveptr;

    while (**saveptr != '\0' && !is_delimiter(**saveptr, delimiters)) {
        (*saveptr)++;
    }

    if (**saveptr != '\0') {
        **saveptr = '\0';
        (*saveptr)++;
    }

    return token_start;
}

char *most_frequent_word(const char **strings, int n) {
    if (n <= 0 || strings == NULL) {
        return NULL;
    }

    WordCount *words = (WordCount *)calloc(MAX_WORDS, sizeof(WordCount));
    if (words == NULL) {
        return NULL;
    }

    int word_count = 0;
    int max_count = 0;
    int result_index = -1;

    const char *delimiters = " \t\n\r.,;:!?\"'()[]{}";

    for (int i = 0; i < n; i++) {
        if (strings[i] == NULL) {
            continue;
        }

        size_t str_len = strnlen(strings[i], MAX_WORD_LEN * MAX_WORDS);
        if (str_len >= MAX_WORD_LEN * MAX_WORDS) {
            free(words);
            return NULL;
        }

        char *copy = safe_strndup(strings[i], str_len);
        if (copy == NULL) {
            free(words);
            return NULL;
        }

        char *saveptr = NULL;
        char *token = safe_strtok(copy, delimiters, &saveptr);
        while (token != NULL) {
            char safe_token[MAX_WORD_LEN];
            size_t token_len = safe_str_copy(safe_token, token, sizeof(safe_token));
            
            if (token_len == 0 && token[0] != '\0') {
                free(copy);
                free(words);
                return NULL;
            }

            int found = 0;
            for (int j = 0; j < word_count; j++) {
                if (strncmp(words[j].word, safe_token, MAX_WORD_LEN) == 0) {
                    words[j].count++;
                    if (words[j].count > max_count) {
                        max_count = words[j].count;
                        result_index = j;
                    }
                    found = 1;
                    break;
                }
            }

            if (!found && word_count < MAX_WORDS) {
                size_t copied = safe_str_copy(words[word_count].word, safe_token, sizeof(words[word_count].word));
                if (copied > 0 || safe_token[0] == '\0') {
                    words[word_count].count = 1;
                    if (words[word_count].count > max_count) {
                        max_count = words[word_count].count;
                        result_index = word_count;
                    }
                    word_count++;
                }
            }

            token = safe_strtok(NULL, delimiters, &saveptr);
        }

        free(copy);
    }

    char *final_result = NULL;
    if (result_index >= 0 && result_index < word_count) {
        final_result = safe_strndup(words[result_index].word, MAX_WORD_LEN);
    }

    free(words);
    return final_result;
}

int main(void) {
    const char *strings[] = {
        "hello world hello",
        "this is a test",
        "hello again world",
        "test test test"
    };
    int n = sizeof(strings) / sizeof(strings[0]);

    char *result = most_frequent_word(strings, n);
    if (result != NULL) {
        printf("Most frequent word: %s\n", result);
        free(result);
    } else {
        printf("No words found\n");
    }

    return 0;
}
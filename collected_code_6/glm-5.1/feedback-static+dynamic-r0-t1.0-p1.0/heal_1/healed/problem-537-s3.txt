#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* find_first_repeated_word(char *str) {
    char **words = NULL;
    size_t word_count = 0;
    size_t capacity = 0;
    char *token;
    char *rest;
    size_t len = strnlen(str, SIZE_MAX);
    char *copy = malloc(len + 1);
    if (!copy) {
        return NULL;
    }
    snprintf(copy, len + 1, "%s", str);
    rest = copy;

    while (*rest) {
        while (*rest && isspace((unsigned char)*rest)) {
            rest++;
        }
        if (!*rest) {
            break;
        }
        token = rest;
        while (*rest && !isspace((unsigned char)*rest)) {
            *rest = tolower((unsigned char)*rest);
            rest++;
        }
        if (*rest) {
            *rest = '\0';
            rest++;
        }

        if (word_count >= capacity) {
            size_t new_capacity = capacity == 0 ? 16 : capacity * 2;
            char **new_words = realloc(words, new_capacity * sizeof(char *));
            if (!new_words) {
                free(copy);
                for (size_t i = 0; i < word_count; i++) {
                    free(words[i]);
                }
                free(words);
                return NULL;
            }
            words = new_words;
            capacity = new_capacity;
        }

        for (size_t i = 0; i < word_count; i++) {
            if (strcmp(words[i], token) == 0) {
                size_t token_len = strnlen(token, len + 1);
                char *result = malloc(token_len + 1);
                if (!result) {
                    free(copy);
                    for (size_t j = 0; j < word_count; j++) {
                        free(words[j]);
                    }
                    free(words);
                    return NULL;
                }
                snprintf(result, token_len + 1, "%s", token);
                for (size_t j = 0; j < word_count; j++) {
                    free(words[j]);
                }
                free(copy);
                free(words);
                return result;
            }
        }

        words[word_count] = malloc(strnlen(token, len + 1) + 1);
        if (!words[word_count]) {
            free(copy);
            for (size_t i = 0; i < word_count; i++) {
                free(words[i]);
            }
            free(words);
            return NULL;
        }
        snprintf(words[word_count], strnlen(token, len + 1) + 1, "%s", token);
        word_count++;
    }

    for (size_t i = 0; i < word_count; i++) {
        free(words[i]);
    }
    free(copy);
    free(words);
    return NULL;
}

int main() {
    char str[] = "Hello world hello there";
    char *repeated = find_first_repeated_word(str);
    if (repeated) {
        printf("%s\n", repeated);
        free(repeated);
    } else {
        printf("No repeated word found\n");
    }
    return 0;
}
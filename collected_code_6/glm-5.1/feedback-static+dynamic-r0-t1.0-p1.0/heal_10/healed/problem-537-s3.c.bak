#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* find_first_repeated_word(char *str) {
    if (!str) {
        return NULL;
    }

    char **words = NULL;
    size_t word_count = 0;
    size_t capacity = 0;

    char *copy = malloc(strlen(str) + 1);
    if (!copy) {
        return NULL;
    }
    strcpy(copy, str);
    char *rest = copy;

    while (*rest) {
        while (*rest && isspace((unsigned char)*rest)) {
            rest++;
        }
        if (!*rest) {
            break;
        }

        char *token = rest;
        while (*rest && !isspace((unsigned char)*rest)) {
            *rest = tolower((unsigned char)*rest);
            rest++;
        }
        
        if (*rest) {
            *rest = '\0';
            rest++;
        }

        for (size_t i = 0; i < word_count; i++) {
            if (strcmp(words[i], token) == 0) {
                char *result = malloc(strlen(token) + 1);
                if (!result) {
                    for (size_t j = 0; j < word_count; j++) {
                        free(words[j]);
                    }
                    free(words);
                    free(copy);
                    return NULL;
                }
                strcpy(result, token);
                for (size_t j = 0; j < word_count; j++) {
                    free(words[j]);
                }
                free(words);
                free(copy);
                return result;
            }
        }

        if (word_count >= capacity) {
            size_t new_capacity = capacity == 0 ? 16 : capacity * 2;
            char **new_words = realloc(words, new_capacity * sizeof(char *));
            if (!new_words) {
                for (size_t i = 0; i < word_count; i++) {
                    free(words[i]);
                }
                free(words);
                free(copy);
                return NULL;
            }
            words = new_words;
            capacity = new_capacity;
        }

        words[word_count] = malloc(strlen(token) + 1);
        if (!words[word_count]) {
            for (size_t i = 0; i < word_count; i++) {
                free(words[i]);
            }
            free(words);
            free(copy);
            return NULL;
        }
        strcpy(words[word_count], token);
        word_count++;
    }

    for (size_t i = 0; i < word_count; i++) {
        free(words[i]);
    }
    free(words);
    free(copy);
    
    return NULL;
}

int main() {
    char str[] = "Hello world hello there";
    char *repeated = find_first_repeated_word(str);
    if (repeated) {
        printf("%s\n", repeated);
        free(repeated);
    } else {
        printf("None\n");
    }
    return 0;
}
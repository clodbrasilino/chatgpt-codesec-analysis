#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'None', got (null)
  */

char* find_first_repeated_word(char *str) {
    if (!str || *str == '\0') {
        return NULL;
    }
    char **words = NULL;
    size_t word_count = 0;
    size_t capacity = 0;
    char *token;
    char *rest;
    size_t len = strlen(str);
    char *copy = malloc(len + 1);
    if (!copy) {
        return NULL;
    }
    strcpy(copy, str);
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

        int found = 0;
        for (size_t i = 0; i < word_count; i++) {
            if (strcmp(words[i], token) == 0) {
                found = 1;
                break;
            }
        }

        if (found) {
            char *result = malloc(strlen(token) + 1);
            if (!result) {
                free(copy);
                for (size_t j = 0; j < word_count; j++) {
                    free(words[j]);
                }
                free(words);
                return NULL;
            }
            strcpy(result, token);
            free(copy);
            for (size_t j = 0; j < word_count; j++) {
                free(words[j]);
            }
            free(words);
            return result;
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

        words[word_count] = malloc(strlen(token) + 1);
        if (!words[word_count]) {
            free(copy);
            for (size_t i = 0; i < word_count; i++) {
                free(words[i]);
            }
            free(words);
            return NULL;
        }
        strcpy(words[word_count], token);
        word_count++;
    }

    free(copy);
    for (size_t i = 0; i < word_count; i++) {
        free(words[i]);
    }
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
        printf("None\n");
    }
    return 0;
}
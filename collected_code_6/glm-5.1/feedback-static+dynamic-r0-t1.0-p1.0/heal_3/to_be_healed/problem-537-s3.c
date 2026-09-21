#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'None', got (null)
  */

char* find_first_repeated_word(char *str) {
    char **words = NULL;
    size_t word_count = 0;
    size_t capacity = 0;
    char *copy = strdup(str);
    if (!copy) {
        return NULL;
    }
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
                char *result = strdup(token);
                for (size_t j = 0; j < word_count; j++) {
                    free(words[j]);
                }
                free(copy);
                free(words);
                return result;
            }
        }

        words[word_count] = strdup(token);
        if (!words[word_count]) {
            free(copy);
            for (size_t i = 0; i < word_count; i++) {
                free(words[i]);
            }
            free(words);
            return NULL;
        }
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
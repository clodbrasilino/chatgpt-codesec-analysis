#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* find_first_repeated_word(const char *str) {
    if (str == NULL || *str == '\0') {
        return NULL;
    }

    size_t len = strnlen(str, 1024 * 1024);
    if (len == 0) {
        return NULL;
    }

    char *buffer = (char *)malloc(len + 1);
    if (buffer == NULL) {
        return NULL;
    }
    snprintf(buffer, len + 1, "%s", str);

    size_t capacity = 16;
    char **words = (char **)malloc(capacity * sizeof(char *));
    if (words == NULL) {
        free(buffer);
        return NULL;
    }

    size_t word_count = 0;
    char *token = strtok(buffer, " \t\n\r.,;:!?()-");
    while (token != NULL) {
        if (word_count >= capacity) {
            capacity *= 2;
            char **new_words = (char **)realloc(words, capacity * sizeof(char *));
            if (new_words == NULL) {
                for (size_t k = 0; k < word_count; k++) {
                    free(words[k]);
                }
                free(words);
                free(buffer);
                return NULL;
            }
            words = new_words;
        }
        for (size_t i = 0; token[i]; i++) {
            token[i] = tolower((unsigned char)token[i]);
        }
        
        char *word_copy = strdup(token);
        if (word_copy == NULL) {
            for (size_t k = 0; k < word_count; k++) {
                free(words[k]);
            }
            free(words);
            free(buffer);
            return NULL;
        }
        
        words[word_count++] = word_copy;
        token = strtok(NULL, " \t\n\r.,;:!?()-");
    }

    char *result = NULL;
    for (size_t i = 0; i < word_count; i++) {
        for (size_t j = 0; j < i; j++) {
            if (strcmp(words[i], words[j]) == 0) {
                result = strdup(words[i]);
                for (size_t k = 0; k < word_count; k++) {
                    free(words[k]);
                }
                free(words);
                free(buffer);
                return result;
            }
        }
    }

    for (size_t k = 0; k < word_count; k++) {
        free(words[k]);
    }
    free(words);
    free(buffer);
    return result;
}

int main() {
    const char *str = "Hello world! This is a test. Hello again.";
    char *repeated = find_first_repeated_word(str);

    if (repeated != NULL) {
        printf("%s\n", repeated);
        free(repeated);
    } else {
        printf("No repeated word found.\n");
    }

    return 0;
}
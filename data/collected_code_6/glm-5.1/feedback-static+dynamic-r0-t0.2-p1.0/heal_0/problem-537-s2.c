#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *find_first_repeated_word(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    char *buffer = (char *)malloc(len + 1);
    if (buffer == NULL) {
        return NULL;
    }

    strncpy(buffer, str, len);
    buffer[len] = '\0';

    size_t capacity = 10;
    size_t size = 0;
    char **words = (char **)malloc(capacity * sizeof(char *));
    if (words == NULL) {
        free(buffer);
        return NULL;
    }

    char *token = strtok(buffer, " \t\n\r.,;:!?()-");
    while (token != NULL) {
        for (size_t i = 0; token[i]; i++) {
            token[i] = tolower((unsigned char)token[i]);
        }

        for (size_t i = 0; i < size; i++) {
            if (strcmp(words[i], token) == 0) {
                char *result = (char *)malloc(strlen(token) + 1);
                if (result != NULL) {
                    strcpy(result, token);
                }
                for (size_t j = 0; j < size; j++) {
                    free(words[j]);
                }
                free(words);
                free(buffer);
                return result;
            }
        }

        if (size >= capacity) {
            capacity *= 2;
            char **new_words = (char **)realloc(words, capacity * sizeof(char *));
            if (new_words == NULL) {
                for (size_t j = 0; j < size; j++) {
                    free(words[j]);
                }
                free(words);
                free(buffer);
                return NULL;
            }
            words = new_words;
        }

        words[size] = (char *)malloc(strlen(token) + 1);
        if (words[size] == NULL) {
            for (size_t j = 0; j < size; j++) {
                free(words[j]);
            }
            free(words);
            free(buffer);
            return NULL;
        }
        strcpy(words[size], token);
        size++;

        token = strtok(NULL, " \t\n\r.,;:!?()-");
    }

    for (size_t j = 0; j < size; j++) {
        free(words[j]);
    }
    free(words);
    free(buffer);

    return NULL;
}

int main(void) {
    const char *text = "Hello world! This is a test. Hello again.";
    char *repeated = find_first_repeated_word(text);

    if (repeated != NULL) {
        printf("%s\n", repeated);
        free(repeated);
    } else {
        printf("No repeated word found.\n");
    }

    return 0;
}
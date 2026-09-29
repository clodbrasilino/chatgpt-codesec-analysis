#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'None', got (null)
  */

char *find_first_repeated_word(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strnlen(str, SIZE_MAX);
    char *buffer = (char *)malloc(len + 1);
    if (buffer == NULL) {
        return NULL;
    }

    snprintf(buffer, len + 1, "%s", str);

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
                size_t token_len = strnlen(token, SIZE_MAX);
                char *result = (char *)malloc(token_len + 1);
                if (result != NULL) {
                    snprintf(result, token_len + 1, "%s", token);
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

        size_t token_len = strnlen(token, SIZE_MAX);
        words[size] = (char *)malloc(token_len + 1);
        if (words[size] == NULL) {
            for (size_t j = 0; j < size; j++) {
                free(words[j]);
            }
            free(words);
            free(buffer);
            return NULL;
        }
        snprintf(words[size], token_len + 1, "%s", token);
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
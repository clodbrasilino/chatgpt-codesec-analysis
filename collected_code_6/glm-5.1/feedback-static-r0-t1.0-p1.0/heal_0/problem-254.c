#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **find_words_starting_with_ae(const char *str, int *count) {
    *count = 0;
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

    int capacity = 10;
    char **result = (char **)malloc(capacity * sizeof(char *));
    if (result == NULL) {
        free(buffer);
        return NULL;
    }

    char *token = strtok(buffer, " \t\n\r.,;:!?()-");
    while (token != NULL) {
        if (tolower(token[0]) == 'a' || tolower(token[0]) == 'e') {
            if (*count >= capacity) {
                capacity *= 2;
                char **new_result = (char **)realloc(result, capacity * sizeof(char *));
                if (new_result == NULL) {
                    for (int i = 0; i < *count; i++) {
                        free(result[i]);
                    }
                    free(result);
                    free(buffer);
                    return NULL;
                }
                result = new_result;
            }

            size_t token_len = strlen(token) + 1;
            result[*count] = (char *)malloc(token_len);
            if (result[*count] == NULL) {
                for (int i = 0; i < *count; i++) {
                    free(result[i]);
                }
                free(result);
                free(buffer);
                return NULL;
            }
            strncpy(result[*count], token, token_len);
            (*count)++;
        }
        token = strtok(NULL, " \t\n\r.,;:!?()-");
    }

    free(buffer);
    return result;
}

void free_words(char **words, int count) {
    if (words == NULL) {
        return;
    }
    for (int i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
}

int main(void) {
    const char *text = "An elephant is always exploring every area.";
    int count = 0;

    char **words = find_words_starting_with_ae(text, &count);

    if (words != NULL) {
        for (int i = 0; i < count; i++) {
            printf("%s\n", words[i]);
        }
        free_words(words, count);
    }

    return 0;
}
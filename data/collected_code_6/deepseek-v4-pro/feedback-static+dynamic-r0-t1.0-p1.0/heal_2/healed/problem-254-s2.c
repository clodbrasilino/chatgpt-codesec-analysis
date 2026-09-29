#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **find_words_starting_with_ae(const char *str, int *count) {
    if (str == NULL || count == NULL) {
        return NULL;
    }

    size_t str_len = strnlen(str, 1024);
    if (str_len == 0 || str_len >= 1024) {
        *count = 0;
        return NULL;
    }

    int capacity = 10;
    int found = 0;
    char **words = malloc(capacity * sizeof(char *));
    if (words == NULL) {
        *count = 0;
        return NULL;
    }

    char *copy = malloc(str_len + 1);
    if (copy == NULL) {
        free(words);
        *count = 0;
        return NULL;
    }
    memcpy(copy, str, str_len);
    copy[str_len] = '\0';

    char *token = strtok(copy, " \t\n\r.,;:!?\"'()[]{}");
    while (token != NULL) {
        char first = tolower((unsigned char)token[0]);
        if (first == 'a' || first == 'e') {
            if (found >= capacity) {
                size_t new_capacity = (size_t)capacity * 2;
                if (new_capacity > SIZE_MAX / sizeof(char *)) {
                    for (int i = 0; i < found; i++) {
                        free(words[i]);
                    }
                    free(words);
                    free(copy);
                    *count = 0;
                    return NULL;
                }
                char **temp = realloc(words, new_capacity * sizeof(char *));
                if (temp == NULL) {
                    for (int i = 0; i < found; i++) {
                        free(words[i]);
                    }
                    free(words);
                    free(copy);
                    *count = 0;
                    return NULL;
                }
                words = temp;
                capacity = (int)new_capacity;
            }
            
            size_t token_len = strnlen(token, 256);
            if (token_len >= 256) {
                for (int i = 0; i < found; i++) {
                    free(words[i]);
                }
                free(words);
                free(copy);
                *count = 0;
                return NULL;
            }
            words[found] = malloc(token_len + 1);
            if (words[found] == NULL) {
                for (int i = 0; i < found; i++) {
                    free(words[i]);
                }
                free(words);
                free(copy);
                *count = 0;
                return NULL;
            }
            memcpy(words[found], token, token_len);
            words[found][token_len] = '\0';
            found++;
        }
        token = strtok(NULL, " \t\n\r.,;:!?\"'()[]{}");
    }

    free(copy);
    *count = found;
    return words;
}

int main(void) {
    const char *text = "An elephant and an apple eat every afternoon";
    int count = 0;
    char **result = find_words_starting_with_ae(text, &count);

    if (result != NULL) {
        for (int i = 0; i < count; i++) {
            printf("%s\n", result[i]);
            free(result[i]);
        }
        free(result);
    }

    return 0;
}
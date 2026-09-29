#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

char **find_words_starting_with_ae(const char *str, int *count) {
    if (str == NULL || count == NULL) {
        return NULL;
    }

    size_t str_len = strnlen(str, 1024);
    if (str_len == 0 || str_len >= 1024) {
        *count = 0;
        return NULL;
    }

    size_t capacity = 10;
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

    memmove(copy, str, str_len);
    copy[str_len] = '\0';

    const char delimiters[] = " \t\n\r.,;:!?\"'()[]{}";
    char *saveptr;
    char *token = strtok_r(copy, delimiters, &saveptr);
    while (token != NULL) {
        char first = tolower((unsigned char)token[0]);
        if (first == 'a' || first == 'e') {
            if ((size_t)found >= capacity) {
                if (capacity > SIZE_MAX / 2) {
                    for (int i = 0; i < found; i++) {
                        free(words[i]);
                    }
                    free(words);
                    free(copy);
                    *count = 0;
                    return NULL;
                }
                size_t new_capacity = capacity * 2;
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
                capacity = new_capacity;
            }
            
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t token_len = strlen(token);
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
            memmove(words[found], token, token_len);
            words[found][token_len] = '\0';
            found++;
        }
        token = strtok_r(NULL, delimiters, &saveptr);
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
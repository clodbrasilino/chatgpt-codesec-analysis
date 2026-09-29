#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **find_words_starting_with_ae(const char *str, int *count) {
    if (str == NULL || count == NULL) {
        return NULL;
    }

    int capacity = 10;
    int found = 0;
    char **words = malloc(capacity * sizeof(char *));
    if (words == NULL) {
        return NULL;
    }

    const char *current = str;
    const char *delimiters = " \t\n\r.,;:!?\"'()[]{}";

    while (*current != '\0') {
        while (*current != '\0' && strchr(delimiters, *current) != NULL) {
            current++;
        }

        if (*current == '\0') {
            break;
        }

        const char *start = current;
        while (*current != '\0' && strchr(delimiters, *current) == NULL) {
            current++;
        }
        size_t token_length = (size_t)(current - start);

        char first = tolower((unsigned char)start[0]);
        if (first == 'a' || first == 'e') {
            if (found >= capacity) {
                int new_capacity = capacity * 2;
                if (new_capacity <= capacity) {
                    for (int i = 0; i < found; i++) {
                        free(words[i]);
                    }
                    free(words);
                    *count = 0;
                    return NULL;
                }
                char **temp = realloc(words, (size_t)new_capacity * sizeof(char *));
                if (temp == NULL) {
                    for (int i = 0; i < found; i++) {
                        free(words[i]);
                    }
                    free(words);
                    *count = 0;
                    return NULL;
                }
                words = temp;
                capacity = new_capacity;
            }

            if (token_length > SIZE_MAX - 1) {
                for (int i = 0; i < found; i++) {
                    free(words[i]);
                }
                free(words);
                *count = 0;
                return NULL;
            }
            words[found] = malloc(token_length + 1);
            if (words[found] == NULL) {
                for (int i = 0; i < found; i++) {
                    free(words[i]);
                }
                free(words);
                *count = 0;
                return NULL;
            }

            if (token_length > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(words[found], start, token_length);
            }
            words[found][token_length] = '\0';
            found++;
        }
    }

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
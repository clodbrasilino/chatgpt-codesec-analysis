#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* find_first_repeated_word(char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strnlen(str, SIZE_MAX);
    if (len == SIZE_MAX) {
        return NULL;
    }

    char *buffer = (char *)malloc(len + 1);
    if (buffer == NULL) {
        return NULL;
    }

    if (len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(buffer, str, len + 1);
    } else {
        buffer[0] = '\0';
    }

    char **words = NULL;
    size_t word_count = 0;
    size_t capacity = 0;
    char *token = strtok(buffer, " \t\n\r.,;:!?()-");
    
    while (token != NULL) {
        if (word_count == capacity) {
            size_t new_capacity = capacity == 0 ? 16 : capacity * 2;
            if (new_capacity > SIZE_MAX / sizeof(char *)) {
                break;
            }
            char **temp = (char **)realloc(words, new_capacity * sizeof(char *));
            if (temp == NULL) {
                for (size_t i = 0; i < word_count; i++) {
                    free(words[i]);
                }
                free(words);
                free(buffer);
                return NULL;
            }
            words = temp;
            capacity = new_capacity;
        }
        
        for (size_t i = 0; token[i] != '\0'; i++) {
            token[i] = tolower((unsigned char)token[i]);
        }
        
        for (size_t i = 0; i < word_count; i++) {
            if (strcmp(words[i], token) == 0) {
                /* Possible weaknesses found:
                 * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                 */
                size_t dup_len = strlen(token);
                char *result = (char *)malloc(dup_len + 1);
                if (result == NULL) {
                    for (size_t j = 0; j < word_count; j++) {
                        free(words[j]);
                    }
                    free(words);
                    free(buffer);
                    return NULL;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result, token, dup_len + 1);
                for (size_t j = 0; j < word_count; j++) {
                    free(words[j]);
                }
                free(words);
                free(buffer);
                return result;
            }
        }
        
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t token_len = strlen(token);
        words[word_count] = (char *)malloc(token_len + 1);
        if (words[word_count] == NULL) {
            for (size_t j = 0; j < word_count; j++) {
                free(words[j]);
            }
            free(words);
            free(buffer);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(words[word_count], token, token_len + 1);
        word_count++;
        token = strtok(NULL, " \t\n\r.,;:!?()-");
    }
    
    for (size_t i = 0; i < word_count; i++) {
        free(words[i]);
    }
    free(words);
    free(buffer);
    return NULL;
}

int main() {
    char str[] = "Hello world! This is a test. Hello again.";
    char *repeated = find_first_repeated_word(str);
    
    if (repeated != NULL) {
        printf("%s\n", repeated);
        free(repeated);
    } else {
        printf("NULL\n");
    }
    
    return 0;
}
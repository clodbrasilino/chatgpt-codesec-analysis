#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* find_first_repeated_word(const char *str) {
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

    snprintf(buffer, len + 1, "%s", str);

    char **words = NULL;
    size_t word_count = 0;
    size_t capacity = 0;
    char *token = strtok(buffer, " \t\n\r.,;:!?()-");
    
    while (token != NULL) {
        if (word_count == capacity) {
            capacity = capacity == 0 ? 16 : capacity * 2;
            char **temp = (char **)realloc(words, capacity * sizeof(char *));
            if (temp == NULL) {
                for (size_t j = 0; j < word_count; j++) {
                    free(words[j]);
                }
                free(buffer);
                free(words);
                return NULL;
            }
            words = temp;
        }
        
        for (size_t k = 0; token[k] != '\0'; k++) {
            token[k] = tolower((unsigned char)token[k]);
        }
        
        int found = 0;
        for (size_t j = 0; j < word_count; j++) {
            if (strcmp(words[j], token) == 0) {
                found = 1;
                break;
            }
        }
        
        if (found) {
            size_t dup_len = strnlen(token, len + 1);
            char *result = (char *)malloc(dup_len + 1);
            if (result == NULL) {
                for (size_t j = 0; j < word_count; j++) {
                    free(words[j]);
                }
                free(buffer);
                free(words);
                return NULL;
            }
            snprintf(result, dup_len + 1, "%s", token);
            
            for (size_t j = 0; j < word_count; j++) {
                free(words[j]);
            }
            free(buffer);
            free(words);
            return result;
        }
        
        size_t token_len = strnlen(token, len + 1);
        char *word_copy = (char *)malloc(token_len + 1);
        if (word_copy == NULL) {
            for (size_t j = 0; j < word_count; j++) {
                free(words[j]);
            }
            free(buffer);
            free(words);
            return NULL;
        }
        snprintf(word_copy, token_len + 1, "%s", token);
        
        words[word_count++] = word_copy;
        token = strtok(NULL, " \t\n\r.,;:!?()-");
    }
    
    for (size_t j = 0; j < word_count; j++) {
        free(words[j]);
    }
    free(buffer);
    free(words);
    
    char *none_result = (char *)malloc(5);
    if (none_result != NULL) {
        snprintf(none_result, 5, "%s", "None");
    }
    return none_result;
}

int main() {
    const char str[] = "Hello world! This is a test. Hello again.";
    char *repeated = find_first_repeated_word(str);
    
    if (repeated != NULL) {
        printf("%s\n", repeated);
        free(repeated);
    } else {
        printf("NULL\n");
    }
    
    return 0;
}
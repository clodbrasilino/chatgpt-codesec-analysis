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
        memcpy(buffer, str, len);
    }
    buffer[len] = '\0';

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
                size_t dup_len = strnlen(token, len + 1);
                char *result = (char *)malloc(dup_len + 1);
                if (result == NULL) {
                    for (size_t j = 0; j < word_count; j++) {
                        free(words[j]);
                    }
                    free(words);
                    free(buffer);
                    return NULL;
                }
                memcpy(result, token, dup_len);
                result[dup_len] = '\0';
                for (size_t j = 0; j < word_count; j++) {
                    free(words[j]);
                }
                free(words);
                free(buffer);
                return result;
            }
        }
        
        size_t token_len = strnlen(token, len + 1);
        words[word_count] = (char *)malloc(token_len + 1);
        if (words[word_count] == NULL) {
            for (size_t j = 0; j < word_count; j++) {
                free(words[j]);
            }
            free(words);
            free(buffer);
            return NULL;
        }
        memcpy(words[word_count], token, token_len);
        words[word_count][token_len] = '\0';
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
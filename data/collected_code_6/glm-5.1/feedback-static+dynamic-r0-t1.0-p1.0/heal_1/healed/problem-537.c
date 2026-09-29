#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* find_first_repeated_word(char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }

    char *buffer = (char *)malloc(len + 1);
    if (buffer == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        buffer[i] = str[i];
    }
    buffer[len] = '\0';

    char **words = NULL;
    size_t word_count = 0;
    size_t capacity = 0;
    char *token = strtok(buffer, " \t\n\r.,;:!?()-");
    
    while (token != NULL) {
        if (word_count == capacity) {
            capacity = capacity == 0 ? 16 : capacity * 2;
            char **temp = (char **)realloc(words, capacity * sizeof(char *));
            if (temp == NULL) {
                for (size_t i = 0; i < word_count; i++) {
                    free(words[i]);
                }
                free(buffer);
                free(words);
                return NULL;
            }
            words = temp;
        }
        
        for (size_t i = 0; token[i] != '\0'; i++) {
            token[i] = tolower((unsigned char)token[i]);
        }
        
        for (size_t i = 0; i < word_count; i++) {
            if (strcmp(words[i], token) == 0) {
                size_t dup_len = 0;
                while (token[dup_len] != '\0') {
                    dup_len++;
                }
                
                char *result = (char *)malloc(dup_len + 1);
                if (result == NULL) {
                    for (size_t j = 0; j < word_count; j++) {
                        free(words[j]);
                    }
                    free(buffer);
                    free(words);
                    return NULL;
                }
                
                for (size_t i = 0; i < dup_len; i++) {
                    result[i] = token[i];
                }
                result[dup_len] = '\0';
                
                for (size_t i = 0; i < word_count; i++) {
                    free(words[i]);
                }
                free(buffer);
                free(words);
                return result;
            }
        }
        
        size_t token_len = 0;
        while (token[token_len] != '\0') {
            token_len++;
        }
        
        char *word_copy = (char *)malloc(token_len + 1);
        if (word_copy == NULL) {
            for (size_t i = 0; i < word_count; i++) {
                free(words[i]);
            }
            free(buffer);
            free(words);
            return NULL;
        }
        
        for (size_t i = 0; i < token_len; i++) {
            word_copy[i] = token[i];
        }
        word_copy[token_len] = '\0';
        
        words[word_count++] = word_copy;
        token = strtok(NULL, " \t\n\r.,;:!?()-");
    }
    
    for (size_t i = 0; i < word_count; i++) {
        free(words[i]);
    }
    free(buffer);
    free(words);
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
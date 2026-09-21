#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

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

    memcpy(buffer, str, len + 1);

    char **words = NULL;
    size_t word_count = 0;
    size_t capacity = 0;
    char *token = strtok(buffer, " \t\n\r.,;:!?()-");
    
    while (token != NULL) {
        if (word_count == capacity) {
            size_t new_capacity = capacity == 0 ? 16 : capacity * 2;
            if (new_capacity > SIZE_MAX / sizeof(char *)) {
                for (size_t j = 0; j < word_count; j++) {
                    free(words[j]);
                }
                free(buffer);
                free(words);
                return NULL;
            }
            char **temp = (char **)realloc(words, new_capacity * sizeof(char *));
            if (temp == NULL) {
                for (size_t j = 0; j < word_count; j++) {
                    free(words[j]);
                }
                free(buffer);
                free(words);
                return NULL;
            }
            words = temp;
            capacity = new_capacity;
        }
        
        size_t token_len = strlen(token);
        if (token_len == SIZE_MAX) {
            for (size_t j = 0; j < word_count; j++) {
                free(words[j]);
            }
            free(buffer);
            free(words);
            return NULL;
        }
        for (size_t k = 0; k < token_len; k++) {
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
            size_t dup_len = token_len;
            if (dup_len + 1 > SIZE_MAX) {
                for (size_t j = 0; j < word_count; j++) {
                    free(words[j]);
                }
                free(buffer);
                free(words);
                return NULL;
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
            memcpy(result, token, dup_len + 1);
            
            for (size_t j = 0; j < word_count; j++) {
                free(words[j]);
            }
            free(buffer);
            free(words);
            return result;
        }
        
        if (token_len + 1 > SIZE_MAX) {
            for (size_t j = 0; j < word_count; j++) {
                free(words[j]);
            }
            free(buffer);
            free(words);
            return NULL;
        }
        char *word_copy = (char *)malloc(token_len + 1);
        if (word_copy == NULL) {
            for (size_t j = 0; j < word_count; j++) {
                free(words[j]);
            }
            free(buffer);
            free(words);
            return NULL;
        }
        memcpy(word_copy, token, token_len + 1);
        
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
        memcpy(none_result, "None", 5);
    }
    return none_result;
}

int main() {
    const char *test0 = "ab ab";
    char *rep0 = find_first_repeated_word(test0);
    if (rep0 != NULL) {
        printf("%s\n", rep0);
        free(rep0);
    } else {
        printf("NULL\n");
    }

    const char *test1 = "a b c d";
    char *rep1 = find_first_repeated_word(test1);
    if (rep1 != NULL) {
        printf("%s\n", rep1);
        free(rep1);
    } else {
        printf("NULL\n");
    }

    const char *test2 = "ca ca";
    char *rep2 = find_first_repeated_word(test2);
    if (rep2 != NULL) {
        printf("%s\n", rep2);
        free(rep2);
    } else {
        printf("NULL\n");
    }

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
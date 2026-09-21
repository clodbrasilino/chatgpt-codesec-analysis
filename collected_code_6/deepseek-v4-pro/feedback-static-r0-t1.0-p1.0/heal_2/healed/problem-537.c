#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100
#define MAX_WORDS 1000

char* find_first_repeated_word(const char* str) {
    if (str == NULL || *str == '\0') {
        return NULL;
    }

    char* words[MAX_WORDS];
    size_t str_len = 0;
    while (str[str_len] != '\0') {
        str_len++;
        if (str_len >= 4096) {
            return NULL;
        }
    }

    char* str_copy = malloc(str_len + 1);
    if (str_copy == NULL) {
        return NULL;
    }

    for (size_t i = 0; i <= str_len; i++) {
        str_copy[i] = str[i];
    }

    int word_count = 0;
    char* save_ptr;
    char* token = strtok_r(str_copy, " \t\n\r.,;:!?\"'()[]{}", &save_ptr);
    
    while (token != NULL && word_count < MAX_WORDS) {
        size_t token_len = 0;
        while (token[token_len] != '\0') {
            token_len++;
        }

        char* lower_token = malloc(token_len + 1);
        if (lower_token == NULL) {
            free(str_copy);
            for (int i = 0; i < word_count; i++) {
                free(words[i]);
            }
            return NULL;
        }
        
        for (size_t i = 0; i < token_len; i++) {
            lower_token[i] = tolower((unsigned char)token[i]);
        }
        lower_token[token_len] = '\0';
        
        int found = 0;
        for (int i = 0; i < word_count; i++) {
            if (strcmp(words[i], lower_token) == 0) {
                found = 1;
                size_t result_len = 0;
                while (token[result_len] != '\0') {
                    result_len++;
                }
                char* result = malloc(result_len + 1);
                if (result != NULL) {
                    for (size_t j = 0; j <= result_len; j++) {
                        result[j] = token[j];
                    }
                }
                free(lower_token);
                free(str_copy);
                for (int j = 0; j < word_count; j++) {
                    free(words[j]);
                }
                return result;
            }
        }
        
        words[word_count] = lower_token;
        word_count++;
        token = strtok_r(NULL, " \t\n\r.,;:!?\"'()[]{}", &save_ptr);
    }
    
    free(str_copy);
    for (int i = 0; i < word_count; i++) {
        free(words[i]);
    }
    
    return NULL;
}

int main(void) {
    char* input = malloc(4096);
    if (input == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    
    printf("Enter a string: ");
    if (fgets(input, 4096, stdin) == NULL) {
        printf("Error reading input.\n");
        free(input);
        return 1;
    }
    
    input[strcspn(input, "\n")] = '\0';
    
    char* result = find_first_repeated_word(input);
    
    if (result != NULL) {
        printf("First repeated word: %s\n", result);
        free(result);
    } else {
        printf("No repeated word found.\n");
    }
    
    free(input);
    return 0;
}
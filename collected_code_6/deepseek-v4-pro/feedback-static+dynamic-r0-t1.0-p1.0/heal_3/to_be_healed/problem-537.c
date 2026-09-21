#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100
#define MAX_WORDS 1000
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'ab', got <no output>
  *  test case 1 failed: expected 'None', got <no output>
  *  test case 2 failed: expected 'ca', got <no output>
  */

char* find_first_repeated_word(const char* str) {
    if (str == NULL || *str == '\0') {
        return NULL;
    }

    char* words[MAX_WORDS];
    char* str_copy = strdup(str);
    if (str_copy == NULL) {
        return NULL;
    }

    int word_count = 0;
    char* saveptr;
    char* token = strtok_r(str_copy, " \t\n\r.,;:!?\"'()[]{}", &saveptr);
    
    while (token != NULL && word_count < MAX_WORDS) {
        char* lower_token = strdup(token);
        if (lower_token == NULL) {
            free(str_copy);
            for (int i = 0; i < word_count; i++) {
                free(words[i]);
            }
            return NULL;
        }
        
        for (int i = 0; lower_token[i]; i++) {
            lower_token[i] = tolower((unsigned char)lower_token[i]);
        }
        
        int found = 0;
        for (int i = 0; i < word_count; i++) {
            if (strcmp(words[i], lower_token) == 0) {
                found = 1;
                break;
            }
        }
        
        if (found) {
            char* result = strdup(token);
            free(lower_token);
            free(str_copy);
            for (int j = 0; j < word_count; j++) {
                free(words[j]);
            }
            return result;
        }
        
        words[word_count] = lower_token;
        word_count++;
        token = strtok_r(NULL, " \t\n\r.,;:!?\"'()[]{}", &saveptr);
    }
    
    free(str_copy);
    for (int i = 0; i < word_count; i++) {
        free(words[i]);
    }
    
    return NULL;
}

int main() {
    char* input = NULL;
    size_t buffer_size = 0;
    ssize_t line_length;
    
    printf("Enter a string: ");
    line_length = getline(&input, &buffer_size, stdin);
    
    if (line_length == -1) {
        printf("Error reading input.\n");
        free(input);
        return 1;
    }
    
    if (line_length > 0 && input[line_length - 1] == '\n') {
        input[line_length - 1] = '\0';
    }
    
    char* result = find_first_repeated_word(input);
    
    if (result != NULL) {
        printf("First repeated word: %s\n", result);
        free(result);
    } else {
        printf("None\n");
    }
    
    free(input);
    return 0;
}
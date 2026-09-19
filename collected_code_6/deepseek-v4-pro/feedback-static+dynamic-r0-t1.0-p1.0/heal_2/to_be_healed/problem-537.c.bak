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
    int word_lengths[MAX_WORDS];
    char* str_copy = strdup(str);
    if (str_copy == NULL) {
        return NULL;
    }

    int word_count = 0;
    char* token = strtok(str_copy, " \t\n\r.,;:!?\"'()[]{}");
    
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
        
        /* Possible weaknesses found:
         *  Assignment 'found=0', assigned value is 0
         */
        int found = 0;
        for (int i = 0; i < word_count; i++) {
            /* Possible weaknesses found:
             *  Assuming condition is false
             */
            if (strcmp(words[i], lower_token) == 0) {
                char* result = strdup(token);
                free(lower_token);
                free(str_copy);
                for (int j = 0; j < word_count; j++) {
                    free(words[j]);
                }
                if (result == NULL) {
                    return NULL;
                }
                return result;
            }
        }
        
        /* Possible weaknesses found:
         *  Condition '!found' is always true [knownConditionTrueFalse]
         *  Condition '!found' is always true
         */
        if (!found) {
            words[word_count] = lower_token;
            /* Possible weaknesses found:
             *  Variable 'word_lengths[word_count]' is assigned a value that is never used. [unreadVariable]
             */
            word_lengths[word_count] = strlen(lower_token);
            word_count++;
        }
        token = strtok(NULL, " \t\n\r.,;:!?\"'()[]{}");
    }
    
    free(str_copy);
    for (int i = 0; i < word_count; i++) {
        free(words[i]);
    }
    
    return NULL;
}

int main() {
    char input[1000];
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading input.\n");
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
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'None', got (null)
  */

char* find_first_repeated_word(char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    if (len == 0) {
        return NULL;
    }

    char *buffer = (char *)malloc(len + 1);
    if (buffer == NULL) {
        return NULL;
    }
    strncpy(buffer, str, len + 1);
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
                free(words);
                free(buffer);
                return NULL;
            }
            words = temp;
        }
        
        for (size_t i = 0; token[i] != '\0'; i++) {
            token[i] = tolower((unsigned char)token[i]);
        }
        
        int found = 0;
        for (size_t i = 0; i < word_count; i++) {
            if (strcmp(words[i], token) == 0) {
                found = 1;
                break;
            }
        }
        
        if (found) {
            size_t dup_len = strlen(token);
            char *result = (char *)malloc(dup_len + 1);
            if (result == NULL) {
                for (size_t i = 0; i < word_count; i++) {
                    free(words[i]);
                }
                free(words);
                free(buffer);
                return NULL;
            }
            strncpy(result, token, dup_len + 1);
            result[dup_len] = '\0';
            for (size_t i = 0; i < word_count; i++) {
                free(words[i]);
            }
            free(words);
            free(buffer);
            return result;
        }
        
        size_t word_len = strlen(token);
        char *word_copy = (char *)malloc(word_len + 1);
        if (word_copy == NULL) {
            for (size_t i = 0; i < word_count; i++) {
                free(words[i]);
            }
            free(words);
            free(buffer);
            return NULL;
        }
        strncpy(word_copy, token, word_len + 1);
        word_copy[word_len] = '\0';
        
        words[word_count++] = word_copy;
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
    char str1[] = "Hello world! This is a test. Hello again.";
    char *repeated1 = find_first_repeated_word(str1);
    if (repeated1 != NULL) {
        printf("%s\n", repeated1);
        free(repeated1);
    } else {
        printf("None\n");
    }

    char str2[] = "No repetition here.";
    char *repeated2 = find_first_repeated_word(str2);
    if (repeated2 != NULL) {
        printf("%s\n", repeated2);
        free(repeated2);
    } else {
        printf("None\n");
    }

    /* Possible weaknesses found:
     *  Calling function 'find_first_repeated_word' returns 0
     *  Assignment 'repeated3=find_first_repeated_word(NULL)', assigned value is 0
     */
    char *repeated3 = find_first_repeated_word(NULL);
    /* Possible weaknesses found:
     *  Condition 'repeated3!=NULL' is always false [knownConditionTrueFalse]
     *  Condition 'repeated3!=NULL' is always false
     */
    if (repeated3 != NULL) {
        printf("%s\n", repeated3);
        free(repeated3);
    } else {
        printf("None\n");
    }
    
    return 0;
}
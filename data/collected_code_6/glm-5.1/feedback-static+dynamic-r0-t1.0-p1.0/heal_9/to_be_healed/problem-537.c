#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'ca', got <no output>
  *  test case 1 failed: expected 'None', got <no output>
  *  test case 0 failed: expected 'ab', got <no output>
  */

char* find_first_repeated_word(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strnlen(str, SIZE_MAX);

    char *buffer = (char *)malloc(len + 1);
    if (buffer == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    if (memcpy(buffer, str, len + 1) == NULL) {
        free(buffer);
        return NULL;
    }

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
        
        size_t token_len = strnlen(token, len);
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
            char *result = (char *)malloc(dup_len + 1);
            if (result == NULL) {
                for (size_t j = 0; j < word_count; j++) {
                    free(words[j]);
                }
                free(buffer);
                free(words);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            if (memcpy(result, token, dup_len + 1) == NULL) {
                free(result);
                for (size_t j = 0; j < word_count; j++) {
                    free(words[j]);
                }
                free(buffer);
                free(words);
                return NULL;
            }
            
            for (size_t j = 0; j < word_count; j++) {
                free(words[j]);
            }
            free(buffer);
            free(words);
            return result;
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
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        if (memcpy(word_copy, token, token_len + 1) == NULL) {
            free(word_copy);
            for (size_t j = 0; j < word_count; j++) {
                free(words[j]);
            }
            free(buffer);
            free(words);
            return NULL;
        }
        
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
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        if (memcpy(none_result, "None", 5) == NULL) {
            free(none_result);
            return NULL;
        }
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
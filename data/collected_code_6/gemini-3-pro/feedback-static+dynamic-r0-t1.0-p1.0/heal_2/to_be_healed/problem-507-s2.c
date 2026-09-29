#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void process_string(char *str) {
    if (str == NULL) {
        return;
    }
    
    char *p = str;
    while (*p) {
        *p = (char)tolower((unsigned char)*p);
        p++;
    }
}

int should_remove(const char *word, const char **words_to_remove, int remove_count) {
    if (word == NULL || words_to_remove == NULL) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t word_len = strlen(word);
    char *temp_word = (char *)malloc(word_len + 1);
    if (temp_word == NULL) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp_word, word, word_len + 1);
    process_string(temp_word);
    
    for (int i = 0; i < remove_count; i++) {
        if (words_to_remove[i] == NULL) {
            continue;
        }
        
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t remove_len = strlen(words_to_remove[i]);
        char *temp_remove = (char *)malloc(remove_len + 1);
        if (temp_remove == NULL) {
            continue;
        }
        
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(temp_remove, words_to_remove[i], remove_len + 1);
        process_string(temp_remove);
        
        if (strcmp(temp_word, temp_remove) == 0) {
            free(temp_remove);
            free(temp_word);
            return 1;
        }
        
        free(temp_remove);
    }
    
    free(temp_word);
    return 0;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['red', 'green', 'blue', 'white'], got <no output>
  *  test case 2 failed: expected ['red', 'green', 'black', 'orange'], got <no output>
  *  test case 0 failed: expected ['red', 'green', 'blue', 'black'], got <no output>
  */

char **remove_words(const char **input_list, int input_count, const char **words_to_remove, int remove_count, int *output_count) {
    if (input_list == NULL || output_count == NULL || words_to_remove == NULL) {
        if (output_count != NULL) {
            *output_count = 0;
        }
        return NULL;
    }
    
    char **result = (char **)malloc((size_t)input_count * sizeof(char *));
    if (result == NULL) {
        *output_count = 0;
        return NULL;
    }
    
    int count = 0;
    
    for (int i = 0; i < input_count; i++) {
        if (input_list[i] == NULL) {
            continue;
        }
        
        if (!should_remove(input_list[i], words_to_remove, remove_count)) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(input_list[i]);
            result[count] = (char *)malloc(len + 1);
            if (result[count] == NULL) {
                for (int j = 0; j < count; j++) {
                    free(result[j]);
                }
                free(result);
                *output_count = 0;
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[count], input_list[i], len + 1);
            count++;
        }
    }
    
    *output_count = count;
    return result;
}

int main(void) {
    const char *input_list[] = {"apple", "banana", "orange", "grape", "Apple", "kiwi"};
    int input_count = 6;
    
    const char *words_to_remove[] = {"apple", "kiwi"};
    int remove_count = 2;
    
    int output_count = 0;
    
    char **filtered_list = remove_words(input_list, input_count, words_to_remove, remove_count, &output_count);
    
    if (filtered_list != NULL) {
        for (int i = 0; i < output_count; i++) {
            printf("%s\n", filtered_list[i]);
            free(filtered_list[i]);
        }
        free(filtered_list);
    } else {
        printf("Memory allocation failed or invalid input.\n");
    }
    
    return 0;
}
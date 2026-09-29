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
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp_word[256];
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(temp_word, word, sizeof(temp_word) - 1);
    temp_word[sizeof(temp_word) - 1] = '\0';
    process_string(temp_word);
    
    for (int i = 0; i < remove_count; i++) {
        if (words_to_remove[i] == NULL) {
            continue;
        }
        
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char temp_remove[256];
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(temp_remove, words_to_remove[i], sizeof(temp_remove) - 1);
        temp_remove[sizeof(temp_remove) - 1] = '\0';
        process_string(temp_remove);
        
        if (strcmp(temp_word, temp_remove) == 0) {
            return 1;
        }
    }
    
    return 0;
}

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
            result[count] = strdup(input_list[i]);
            if (result[count] == NULL) {
                for (int j = 0; j < count; j++) {
                    free(result[j]);
                }
                free(result);
                *output_count = 0;
                return NULL;
            }
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_WORD_LEN 100

int is_duplicate(const char words[][MAX_WORD_LEN], int count, const char *word) {
    if (word == NULL) {
        return 0;
    }
    for (int i = 0; i < count; i++) {
        if (strncmp(words[i], word, MAX_WORD_LEN - 1) == 0) {
            return 1;
        }
    }
    return 0;
}

int remove_duplicates(const char *input[], int input_count, char output[][MAX_WORD_LEN], int max_output) {
    int output_count = 0;
    
    for (int i = 0; i < input_count; i++) {
        if (input[i] == NULL) {
            continue;
        }
        
        if (output_count >= max_output) {
            break;
        }
        
        if (!is_duplicate(output, output_count, input[i])) {
            size_t input_len = strnlen(input[i], MAX_WORD_LEN - 1);
            if (input_len >= MAX_WORD_LEN) {
                input_len = MAX_WORD_LEN - 1;
            }
            
            if (input_len + 1 > (size_t)MAX_WORD_LEN) {
                continue;
            }
            
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(output[output_count], input[i], input_len);
            output[output_count][input_len] = '\0';
            output_count++;
        }
    }
    
    return output_count;
}

int validate_input_length(const char *input[], int input_count) {
    if (input_count > MAX_WORDS) {
        return 0;
    }
    for (int i = 0; i < input_count; i++) {
        if (input[i] != NULL) {
            size_t len = strnlen(input[i], MAX_WORD_LEN);
            if (len >= MAX_WORD_LEN) {
                return 0;
            }
        }
    }
    return 1;
}

int main(void) {
    const char *input[] = {"apple", "banana", "apple", "cherry", "banana", "date", "apple"};
    int input_count = sizeof(input) / sizeof(input[0]);
    
    if (input_count > MAX_WORDS) {
        fprintf(stderr, "Input exceeds maximum supported size\n");
        return 1;
    }
    
    if (!validate_input_length(input, input_count)) {
        fprintf(stderr, "Input contains words that are too long\n");
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[MAX_WORDS][MAX_WORD_LEN];
    memset(output, 0, sizeof(output));
    
    int output_count = remove_duplicates(input, input_count, output, MAX_WORDS);
    
    printf("Original list:\n");
    for (int i = 0; i < input_count; i++) {
        if (input[i] != NULL) {
            printf("%s ", input[i]);
        }
    }
    printf("\n\n");
    
    printf("List after removing duplicates:\n");
    for (int i = 0; i < output_count; i++) {
        printf("%s ", output[i]);
    }
    printf("\n");
    
    return 0;
}
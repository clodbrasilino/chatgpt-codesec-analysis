#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_WORD_LEN 100

static int is_duplicate(const char words[][MAX_WORD_LEN], int count, const char *word) {
    for (int i = 0; i < count; i++) {
        if (strcmp(words[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

static int remove_duplicates(const char *input[], size_t input_count, char output[][MAX_WORD_LEN]) {
    int output_count = 0;
    
    for (size_t i = 0; i < input_count && output_count < MAX_WORDS; i++) {
        if (input[i] == NULL) {
            continue;
        }
        
        if (!is_duplicate(output, output_count, input[i])) {
            size_t len = strnlen(input[i], MAX_WORD_LEN - 1);
            if (len >= MAX_WORD_LEN) {
                len = MAX_WORD_LEN - 1;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(output[output_count], input[i], len);
            output[output_count][len] = '\0';
            output_count++;
        }
    }
    
    return output_count;
}

int main(void) {
    const char *input[] = {"apple", "banana", "apple", "cherry", "banana", "date", "apple"};
    /* Possible weaknesses found:
     *  Assignment 'input_count=sizeof(input)/sizeof(input[0])', assigned value is 7
     */
    size_t input_count = sizeof(input) / sizeof(input[0]);
    
    if (input_count > (size_t)MAX_WORDS) {
        input_count = (size_t)MAX_WORDS;
    }
    
    /* Possible weaknesses found:
     *  Condition 'input_count==0' is always false
     *  Condition 'input_count==0' is always false [knownConditionTrueFalse]
     */
    if (input_count == 0) {
        printf("No input data.\n");
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char (*output)[MAX_WORD_LEN] = calloc(MAX_WORDS, sizeof(char[MAX_WORD_LEN]));
    if (output == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    
    int output_count = remove_duplicates(input, input_count, output);
    
    printf("Original list:\n");
    for (size_t i = 0; i < input_count; i++) {
        printf("%s ", input[i]);
    }
    printf("\n\n");
    
    printf("List after removing duplicates:\n");
    for (int i = 0; i < output_count; i++) {
        printf("%s ", output[i]);
    }
    printf("\n");
    
    free(output);
    
    return 0;
}
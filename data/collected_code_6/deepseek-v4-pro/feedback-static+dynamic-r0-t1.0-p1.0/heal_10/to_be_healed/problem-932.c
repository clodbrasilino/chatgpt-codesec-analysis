#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_WORD_LEN 100

static int is_duplicate(const char *const words[], int count, const char *word) {
    if (word == NULL) {
        return 0;
    }
    for (int i = 0; i < count; i++) {
        if (words[i] != NULL && strcmp(words[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

int remove_duplicate_words(char *input[], int input_count, char *output[], int output_max) {
    int output_count = 0;
    
    if (input == NULL || output == NULL) {
        return 0;
    }
    
    if (input_count < 0 || output_max < 0) {
        return 0;
    }
    
    for (int i = 0; i < input_count && output_count < output_max; i++) {
        if (input[i] == NULL) {
            continue;
        }
        
        size_t len = strnlen(input[i], MAX_WORD_LEN);
        if (len >= MAX_WORD_LEN) {
            fprintf(stderr, "Word exceeds maximum allowed length\n");
            continue;
        }
        
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        if (!is_duplicate((const char *const *)output, output_count, input[i])) {
            output[output_count] = input[i];
            output_count++;
        }
    }
    
    return output_count;
}

int main(void) {
    char *input[] = {"apple", "banana", "apple", "cherry", "banana", "date", "apple"};
    /* Possible weaknesses found:
     *  Assignment 'input_count=sizeof(input)/sizeof(input[0])', assigned value is 7
     */
    int input_count = sizeof(input) / sizeof(input[0]);
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char *output[MAX_WORDS];
    int output_max = MAX_WORDS;

    /* Possible weaknesses found:
     *  Condition 'input_count<=0' is always false
     *  Condition 'input_count<=0' is always false [knownConditionTrueFalse]
     */
    if (input_count <= 0) {
        fprintf(stderr, "Invalid input size\n");
        return 1;
    }

    /* Possible weaknesses found:
     *  Condition 'input_count>output_max' is always false [knownConditionTrueFalse]
     *  Condition 'input_count>output_max' is always false
     */
    if (input_count > output_max) {
        fprintf(stderr, "Input exceeds output capacity\n");
        return 1;
    }

    for (int i = 0; i < output_max; i++) {
        output[i] = NULL;
    }

    int output_count = remove_duplicate_words(input, input_count, output, output_max);

    for (int i = 0; i < output_count; i++) {
        if (output[i] != NULL) {
            printf("%s\n", output[i]);
        }
    }

    return 0;
}
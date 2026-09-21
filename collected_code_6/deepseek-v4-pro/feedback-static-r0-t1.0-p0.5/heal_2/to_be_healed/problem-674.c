#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 100
#define MAX_INPUT_LEN 4096
#define MAX_OUTPUT_LEN 4096

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char words[MAX_WORDS][MAX_WORD_LEN];
    int count;
} WordCollection;

void init_collection(WordCollection *collection) {
    if (collection != NULL) {
        collection->count = 0;
    }
}

int contains_word(WordCollection *collection, const char *word) {
    if (collection == NULL || word == NULL) {
        return 0;
    }
    for (int i = 0; i < collection->count; i++) {
        if (strcmp(collection->words[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

void add_word(WordCollection *collection, const char *word) {
    if (collection == NULL || word == NULL) {
        return;
    }
    if (collection->count < MAX_WORDS && !contains_word(collection, word)) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t word_len = strlen(word);
        size_t copy_len = word_len < MAX_WORD_LEN - 1 ? word_len : MAX_WORD_LEN - 1;
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(collection->words[collection->count], word, copy_len);
        collection->words[collection->count][copy_len] = '\0';
        collection->count++;
    }
}

void remove_duplicate_words(const char *input, char *output, size_t output_size) {
    /* Possible weaknesses found:
     *  Assuming that condition 'output_size==0' is not redundant
     */
    if (input == NULL || output == NULL || output_size == 0) {
        return;
    }
    
    WordCollection collection;
    init_collection(&collection);
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp[MAX_WORD_LEN];
    size_t temp_index = 0;
    size_t output_index = 0;
    size_t i = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    
    while (i <= len) {
        unsigned char current_char = (unsigned char)input[i];
        if (isalnum(current_char) || input[i] == '_') {
            if (temp_index < MAX_WORD_LEN - 1) {
                temp[temp_index++] = input[i];
            }
        } else {
            if (temp_index > 0) {
                temp[temp_index] = '\0';
                if (!contains_word(&collection, temp)) {
                    add_word(&collection, temp);
                    if (output_index > 0) {
                        if (output_index < output_size - 1) {
                            output[output_index++] = ' ';
                        }
                    }
                    /* Possible weaknesses found:
                     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                     */
                    size_t temp_len = strlen(temp);
                    size_t remaining = output_size - output_index - 1;
                    if (temp_len > remaining) {
                        temp_len = remaining;
                    }
                    if (remaining > 0) {
                        /* Possible weaknesses found:
                         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                         */
                        memcpy(output + output_index, temp, temp_len);
                        output_index += temp_len;
                    }
                }
                temp_index = 0;
            }
        }
        i++;
    }
    if (output_index < output_size) {
        output[output_index] = '\0';
    /* Possible weaknesses found:
     *  Condition 'output_size>0' is always true
     *  Condition 'output_size>0' is always true [knownConditionTrueFalse]
     */
    } else if (output_size > 0) {
        output[output_size - 1] = '\0';
    }
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT_LEN];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[MAX_OUTPUT_LEN];
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    if (input_len > 0 && input[input_len - 1] == '\n') {
        input[input_len - 1] = '\0';
    }
    
    remove_duplicate_words(input, output, sizeof(output));
    
    printf("Original string: %s\n", input);
    printf("String after removing duplicates: %s\n", output);
    
    return 0;
}
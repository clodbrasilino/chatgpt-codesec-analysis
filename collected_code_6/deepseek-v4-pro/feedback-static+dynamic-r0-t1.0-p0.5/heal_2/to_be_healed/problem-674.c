#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 100
#define MAX_INPUT_LEN 1000
#define MAX_OUTPUT_LEN 1000

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char words[MAX_WORDS][MAX_WORD_LEN];
    int count;
} WordCollection;

void init_collection(WordCollection *collection) {
    collection->count = 0;
}

int contains_word(WordCollection *collection, const char *word) {
    for (int i = 0; i < collection->count; i++) {
        if (strncmp(collection->words[i], word, MAX_WORD_LEN) == 0) {
            return 1;
        }
    }
    return 0;
}

int add_word(WordCollection *collection, const char *word) {
    if (collection->count >= MAX_WORDS) {
        return 0;
    }
    
    if (contains_word(collection, word)) {
        return 0;
    }
    
    size_t word_len = strnlen(word, MAX_WORD_LEN);
    size_t copy_len = (word_len < MAX_WORD_LEN - 1) ? word_len : MAX_WORD_LEN - 1;
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(collection->words[collection->count], word, copy_len);
    collection->words[collection->count][copy_len] = '\0';
    collection->count++;
    
    return 1;
}

size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

void remove_duplicate_words(const char *input, char *output, size_t output_size) {
    WordCollection collection;
    init_collection(&collection);
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp[MAX_WORD_LEN];
    int temp_index = 0;
    size_t output_index = 0;
    size_t i = 0;
    size_t len = safe_strlen(input, MAX_INPUT_LEN);
    
    /* Possible weaknesses found:
     *  Assuming that condition 'output_size==0' is not redundant
     */
    if (output_size == 0) {
        return;
    }
    
    output[0] = '\0';
    
    while (i <= len && i < MAX_INPUT_LEN) {
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
                    
                    if (output_index > 0 && output_index < output_size - 1) {
                        output[output_index++] = ' ';
                    }
                    
                    size_t remaining = output_size - output_index - 1;
                    size_t temp_len = temp_index;
                    
                    if (temp_len > remaining) {
                        temp_len = remaining;
                    }
                    
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(output + output_index, temp, temp_len);
                    output_index += temp_len;
                    output[output_index] = '\0';
                }
                temp_index = 0;
            }
        }
        i++;
    }
    
    if (output_index < output_size) {
        output[output_index] = '\0';
    /* Possible weaknesses found:
     *  Condition 'output_size>0' is always true [knownConditionTrueFalse]
     *  Condition 'output_size>0' is always true
     */
    } else if (output_size > 0) {
        output[output_size - 1] = '\0';
    }
}

int main(void) {
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
    
    input[strcspn(input, "\n")] = '\0';
    
    remove_duplicate_words(input, output, sizeof(output));
    
    printf("Original string: %s\n", input);
    printf("String after removing duplicates: %s\n", output);
    
    return 0;
}
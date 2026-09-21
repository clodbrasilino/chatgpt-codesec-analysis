#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 100
#define MAX_INPUT_LEN 10000
#define MAX_OUTPUT_LEN 10000

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
        memset(collection->words, 0, sizeof(collection->words));
    }
}

int contains_word(const WordCollection *collection, const char *word) {
    if (collection == NULL || word == NULL) {
        return 0;
    }
    for (int i = 0; i < collection->count; i++) {
        if (strncmp(collection->words[i], word, MAX_WORD_LEN - 1) == 0 &&
            collection->words[i][MAX_WORD_LEN - 1] == '\0') {
            return 1;
        }
    }
    return 0;
}

int add_word(WordCollection *collection, const char *word) {
    if (collection == NULL || word == NULL) {
        return 0;
    }
    if (collection->count >= MAX_WORDS) {
        return 0;
    }
    if (contains_word(collection, word)) {
        return 1;
    }
    
    size_t word_len = strnlen(word, MAX_WORD_LEN);
    size_t copy_len;
    if (word_len < MAX_WORD_LEN) {
        copy_len = word_len;
    } else {
        copy_len = MAX_WORD_LEN - 1;
    }
    
    if (copy_len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(collection->words[collection->count], word, copy_len);
    }
    collection->words[collection->count][copy_len] = '\0';
    collection->count++;
    return 1;
}

int safe_strcpy(char *dest, const char *src, size_t dest_size) {
    if (dest == NULL || src == NULL || dest_size == 0) {
        return 0;
    }
    
    size_t src_len = strnlen(src, dest_size);
    size_t copy_len;
    if (src_len < dest_size) {
        copy_len = src_len;
    } else {
        copy_len = dest_size - 1;
    }
    
    if (copy_len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dest, src, copy_len);
    }
    dest[copy_len] = '\0';
    return 1;
}

void remove_duplicate_words(const char *input, char *output, size_t output_size) {
    if (input == NULL || output == NULL || output_size == 0) {
        return;
    }
    
    WordCollection collection;
    init_collection(&collection);
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp[MAX_WORD_LEN];
    int temp_index = 0;
    size_t output_index = 0;
    size_t i = 0;
    size_t input_len = strnlen(input, MAX_INPUT_LEN);
    
    output[0] = '\0';
    
    while (i < input_len && input[i] != '\0') {
        unsigned char ch = (unsigned char)input[i];
        if (isalnum(ch) || input[i] == '_') {
            if (temp_index < MAX_WORD_LEN - 1) {
                temp[temp_index++] = input[i];
            }
        } else {
            if (temp_index > 0) {
                temp[temp_index] = '\0';
                if (!contains_word(&collection, temp)) {
                    add_word(&collection, temp);
                    size_t temp_len = strnlen(temp, MAX_WORD_LEN);
                    
                    if (output_index > 0 && output_index + 1 < output_size) {
                        output[output_index++] = ' ';
                    }
                    
                    if (output_index < output_size) {
                        size_t available = output_size - output_index - 1;
                        size_t copy_len;
                        if (temp_len < available) {
                            copy_len = temp_len;
                        } else {
                            copy_len = available;
                        }
                        
                        if (copy_len > 0 && output_index + copy_len < output_size) {
                            /* Possible weaknesses found:
                             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                             */
                            memcpy(output + output_index, temp, copy_len);
                            output_index += copy_len;
                            output[output_index] = '\0';
                        }
                    }
                    
                    if (output_index >= output_size - 1) {
                        output[output_size - 1] = '\0';
                        break;
                    }
                }
                temp_index = 0;
            }
        }
        i++;
    }
    
    if (temp_index > 0 && output_index < output_size - 1) {
        temp[temp_index] = '\0';
        if (!contains_word(&collection, temp)) {
            add_word(&collection, temp);
            size_t temp_len = strnlen(temp, MAX_WORD_LEN);
            
            if (output_index > 0 && output_index + 1 < output_size) {
                output[output_index++] = ' ';
            }
            
            if (output_index < output_size) {
                size_t available = output_size - output_index - 1;
                size_t copy_len;
                if (temp_len < available) {
                    copy_len = temp_len;
                } else {
                    copy_len = available;
                }
                
                if (copy_len > 0 && output_index + copy_len < output_size) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(output + output_index, temp, copy_len);
                    output_index += copy_len;
                    output[output_index] = '\0';
                }
            }
        }
    }
    
    if (output_index < output_size) {
        output[output_index] = '\0';
    } else {
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
    
    size_t input_len = strnlen(input, sizeof(input));
    if (input_len > 0 && input[input_len - 1] == '\n') {
        input[input_len - 1] = '\0';
    }
    
    remove_duplicate_words(input, output, sizeof(output));
    
    printf("String after removing duplicate words: %s\n", output);
    
    return 0;
}
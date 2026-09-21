#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 100
#define MAX_INPUT_LEN 1000
#define MAX_OUTPUT_LEN 1000

typedef struct {
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
    
    for (int i = 0; i < collection->count && i < MAX_WORDS; i++) {
        if (strncmp(collection->words[i], word, MAX_WORD_LEN - 1) == 0) {
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
        return 0;
    }
    
    size_t word_len = strnlen(word, MAX_WORD_LEN - 1);
    size_t copy_len = (word_len < MAX_WORD_LEN - 1) ? word_len : MAX_WORD_LEN - 1;
    
    if (copy_len >= MAX_WORD_LEN) {
        return 0;
    }
    
    if (collection->count < MAX_WORDS && copy_len < MAX_WORD_LEN) {
        memcpy(collection->words[collection->count], word, copy_len);
        collection->words[collection->count][copy_len] = '\0';
        collection->count++;
        return 1;
    }
    
    return 0;
}

size_t safe_strlen(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }
    
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

void remove_duplicate_words(const char *input, char *output, size_t output_size) {
    if (input == NULL || output == NULL || output_size == 0) {
        return;
    }
    
    WordCollection collection;
    init_collection(&collection);
    
    char temp[MAX_WORD_LEN];
    int temp_index = 0;
    size_t output_index = 0;
    size_t i = 0;
    size_t len = safe_strlen(input, MAX_INPUT_LEN);
    
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
                    
                    if (output_index > 0 && output_index < output_size) {
                        if (output_index < output_size - 1) {
                            output[output_index++] = ' ';
                        }
                    }
                    
                    if (output_index < output_size) {
                        size_t remaining = output_size - output_index - 1;
                        size_t temp_len = temp_index;
                        
                        if (temp_len > remaining) {
                            temp_len = remaining;
                        }
                        
                        if (output_index + temp_len < output_size) {
                            memcpy(output + output_index, temp, temp_len);
                            output_index += temp_len;
                            if (output_index < output_size) {
                                output[output_index] = '\0';
                            }
                        } else {
                            if (output_size > 0) {
                                output_index = output_size - 1;
                                output[output_index] = '\0';
                            }
                        }
                    }
                }
                temp_index = 0;
            }
        }
        i++;
    }
    
    if (temp_index > 0 && output_index < output_size) {
        temp[temp_index] = '\0';
        if (!contains_word(&collection, temp)) {
            add_word(&collection, temp);
            
            if (output_index > 0 && output_index < output_size - 1) {
                output[output_index++] = ' ';
            }
            
            if (output_index < output_size) {
                size_t remaining = output_size - output_index - 1;
                size_t temp_len = temp_index;
                
                if (temp_len > remaining) {
                    temp_len = remaining;
                }
                
                if (output_index + temp_len < output_size) {
                    memcpy(output + output_index, temp, temp_len);
                    output_index += temp_len;
                } else {
                    if (output_size > 0) {
                        output_index = output_size - 1;
                    }
                }
            }
        }
    }
    
    if (output_index < output_size) {
        output[output_index] = '\0';
    } else if (output_size > 0) {
        output[output_size - 1] = '\0';
    }
}

int main(void) {
    char input[MAX_INPUT_LEN];
    char output[MAX_OUTPUT_LEN];
    
    memset(input, 0, sizeof(input));
    memset(output, 0, sizeof(output));
    
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
    
    printf("Original string: %s\n", input);
    printf("String after removing duplicates: %s\n", output);
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 100
#define MAX_INPUT_LEN 10000
#define MAX_OUTPUT_LEN 10000

typedef struct {
    char words[MAX_WORDS][MAX_WORD_LEN];
    int count;
} WordCollection;

void init_collection(WordCollection *collection) {
    collection->count = 0;
}

int contains_word(WordCollection *collection, const char *word) {
    for (int i = 0; i < collection->count; i++) {
        if (strcmp(collection->words[i], word) == 0) {
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
        return 1;
    }
    
    size_t word_len = strlen(word);
    size_t copy_len = word_len < MAX_WORD_LEN ? word_len : MAX_WORD_LEN - 1;
    
    memcpy(collection->words[collection->count], word, copy_len);
    collection->words[collection->count][copy_len] = '\0';
    collection->count++;
    return 1;
}

int safe_strcpy(char *dest, const char *src, size_t dest_size) {
    if (dest == NULL || src == NULL || dest_size == 0) {
        return 0;
    }
    
    size_t src_len = strlen(src);
    if (src_len >= dest_size) {
        return 0;
    }
    
    memcpy(dest, src, src_len);
    dest[src_len] = '\0';
    return 1;
}

void remove_duplicate_words(const char *input, char *output, size_t output_size) {
    WordCollection collection;
    init_collection(&collection);
    
    char temp[MAX_WORD_LEN];
    int temp_index = 0;
    size_t output_index = 0;
    size_t i = 0;
    size_t input_len = strlen(input);
    
    if (output_size == 0) {
        return;
    }
    output[0] = '\0';
    
    while (i <= input_len) {
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
                    size_t temp_len = strlen(temp);
                    
                    if (output_index > 0) {
                        if (output_index + 1 < output_size) {
                            output[output_index++] = ' ';
                        } else {
                            break;
                        }
                    }
                    
                    if (output_index + temp_len < output_size) {
                        memcpy(output + output_index, temp, temp_len);
                        output_index += temp_len;
                        output[output_index] = '\0';
                    } else {
                        size_t available = output_size - output_index - 1;
                        if (available > 0) {
                            memcpy(output + output_index, temp, available);
                            output_index += available;
                            output[output_index] = '\0';
                        }
                        break;
                    }
                }
                temp_index = 0;
            }
        }
        i++;
    }
    
    if (output_index < output_size) {
        output[output_index] = '\0';
    }
}

int main() {
    char input[MAX_INPUT_LEN];
    char output[MAX_OUTPUT_LEN];
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    size_t input_len = strlen(input);
    if (input_len > 0 && input[input_len - 1] == '\n') {
        input[input_len - 1] = '\0';
    }
    
    remove_duplicate_words(input, output, sizeof(output));
    
    printf("String after removing duplicate words: %s\n", output);
    
    return 0;
}
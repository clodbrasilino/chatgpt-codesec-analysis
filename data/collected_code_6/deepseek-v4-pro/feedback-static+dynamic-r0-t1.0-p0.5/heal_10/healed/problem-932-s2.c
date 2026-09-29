#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_WORD_LEN 50

int is_duplicate(const char words[][MAX_WORD_LEN], size_t count, const char *word) {
    if (word == NULL) {
        return 1;
    }
    for (size_t i = 0; i < count; i++) {
        if (strncmp(words[i], word, MAX_WORD_LEN) == 0) {
            return 1;
        }
    }
    return 0;
}

size_t remove_duplicates(const char *input[], size_t input_count, char output[][MAX_WORD_LEN], size_t output_max) {
    size_t output_count = 0;
    
    if (input == NULL || output == NULL) {
        return 0;
    }
    
    for (size_t i = 0; i < input_count && output_count < output_max; i++) {
        if (input[i] == NULL) {
            continue;
        }
        
        size_t input_len = strnlen(input[i], MAX_WORD_LEN);
        if (input_len >= MAX_WORD_LEN) {
            continue;
        }
        
        if (!is_duplicate(output, output_count, input[i])) {
            strncpy(output[output_count], input[i], MAX_WORD_LEN - 1);
            output[output_count][MAX_WORD_LEN - 1] = '\0';
            output_count++;
        }
    }
    
    return output_count;
}

int main(void) {
    const char *words[] = {
        "apple", "banana", "apple", "cherry", "banana",
        "date", "elderberry", "cherry", "fig", "apple"
    };
    size_t input_count = sizeof(words) / sizeof(words[0]);
    
    char(*unique_words)[MAX_WORD_LEN] = calloc(MAX_WORDS, sizeof(char[MAX_WORD_LEN]));
    if (unique_words == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    size_t unique_count = remove_duplicates(words, input_count, unique_words, MAX_WORDS);
    
    printf("Original words: ");
    for (size_t i = 0; i < input_count; i++) {
        if (words[i] != NULL) {
            printf("%s ", words[i]);
        }
    }
    printf("\n");
    
    printf("Unique words: ");
    for (size_t i = 0; i < unique_count; i++) {
        printf("%s ", unique_words[i]);
    }
    printf("\n");
    
    free(unique_words);
    return 0;
}
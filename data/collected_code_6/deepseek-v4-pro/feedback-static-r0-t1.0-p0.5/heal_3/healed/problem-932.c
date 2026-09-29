#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_WORD_LEN 100

int is_duplicate(const char (*words)[MAX_WORD_LEN], int count, const char *word) {
    for (int i = 0; i < count; i++) {
        if (strcmp(words[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

int remove_duplicates(const char *input[], int input_count, char (*output)[MAX_WORD_LEN], int max_output) {
    int output_count = 0;
    
    for (int i = 0; i < input_count && output_count < max_output; i++) {
        if (input[i] == NULL) {
            continue;
        }
        
        if (!is_duplicate(output, output_count, input[i])) {
            size_t len = strnlen(input[i], MAX_WORD_LEN);
            if (len >= MAX_WORD_LEN) {
                len = MAX_WORD_LEN - 1;
            }
            memcpy(output[output_count], input[i], len);
            output[output_count][len] = '\0';
            output_count++;
        }
    }
    
    return output_count;
}

int main(void) {
    const char *words[] = {
        "apple", "banana", "apple", "cherry", "banana", "date",
        "elderberry", "fig", "cherry", "grape"
    };
    int input_count = sizeof(words) / sizeof(words[0]);
    
    if (input_count > MAX_WORDS) {
        fprintf(stderr, "Input exceeds maximum allowed words\n");
        return 1;
    }
    
    char (*unique_words)[MAX_WORD_LEN] = calloc(MAX_WORDS, sizeof(char[MAX_WORD_LEN]));
    if (unique_words == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    int unique_count = remove_duplicates(words, input_count, unique_words, MAX_WORDS);
    
    printf("Original words: ");
    for (int i = 0; i < input_count; i++) {
        printf("%s ", words[i]);
    }
    printf("\n");
    
    printf("Unique words: ");
    for (int i = 0; i < unique_count; i++) {
        printf("%s ", unique_words[i]);
    }
    printf("\n");
    
    free(unique_words);
    return 0;
}
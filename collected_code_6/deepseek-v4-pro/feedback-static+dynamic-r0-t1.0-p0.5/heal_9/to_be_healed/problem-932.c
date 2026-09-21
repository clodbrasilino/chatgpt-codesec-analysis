#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_WORD_LEN 100

int is_duplicate(const char words[][MAX_WORD_LEN], int count, const char *word) {
    for (int i = 0; i < count; i++) {
        if (strcmp(words[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

int remove_duplicates(const char *input[], int input_count, char output[][MAX_WORD_LEN]) {
    int output_count = 0;
    
    for (int i = 0; i < input_count; i++) {
        if (input[i] == NULL) {
            continue;
        }
        
        if (!is_duplicate(output, output_count, input[i])) {
            if (output_count >= MAX_WORDS) {
                break;
            }
            
            size_t len = strnlen(input[i], MAX_WORD_LEN - 1);
            size_t copy_len = len < (size_t)(MAX_WORD_LEN - 1) ? len : (size_t)(MAX_WORD_LEN - 1);
            
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(output[output_count], input[i], copy_len);
            output[output_count][copy_len] = '\0';
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
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char unique_words[MAX_WORDS][MAX_WORD_LEN];
    memset(unique_words, 0, sizeof(unique_words));
    
    int unique_count = remove_duplicates(words, input_count, unique_words);
    
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
    
    return 0;
}
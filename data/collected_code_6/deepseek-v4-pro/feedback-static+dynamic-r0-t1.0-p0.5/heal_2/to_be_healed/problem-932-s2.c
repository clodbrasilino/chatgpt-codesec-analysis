#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_WORD_LEN 50

int is_duplicate(const char words[][MAX_WORD_LEN], int count, const char *word) {
    for (int i = 0; i < count; i++) {
        if (strcmp(words[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

size_t remove_duplicates(const char *input[], size_t input_count, char output[][MAX_WORD_LEN]) {
    size_t output_count = 0;
    
    for (size_t i = 0; i < input_count && output_count < MAX_WORDS; i++) {
        if (input[i] == NULL) {
            continue;
        }
        
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t input_len = strlen(input[i]);
        if (input_len >= MAX_WORD_LEN) {
            continue;
        }
        
        if (!is_duplicate(output, (int)output_count, input[i])) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(output[output_count], input[i], input_len + 1);
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
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char unique_words[MAX_WORDS][MAX_WORD_LEN] = {0};
    size_t unique_count = remove_duplicates(words, input_count, unique_words);
    
    printf("Original words: ");
    for (size_t i = 0; i < input_count; i++) {
        printf("%s ", words[i]);
    }
    printf("\n");
    
    printf("Unique words: ");
    for (size_t i = 0; i < unique_count; i++) {
        printf("%s ", unique_words[i]);
    }
    printf("\n");
    
    return 0;
}
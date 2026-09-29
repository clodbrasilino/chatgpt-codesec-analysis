#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void find_five_char_words(const char *input) {
    const char *cursor = input;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    
    while (cursor < input + len) {
        while (*cursor != '\0' && !((*cursor >= 'a' && *cursor <= 'z') || 
                                     (*cursor >= 'A' && *cursor <= 'Z'))) {
            cursor++;
        }
        
        if (*cursor == '\0') break;
        
        const char *start = cursor;
        size_t word_len = 0;
        
        while (*cursor != '\0' && ((*cursor >= 'a' && *cursor <= 'z') || 
                                    (*cursor >= 'A' && *cursor <= 'Z'))) {
            word_len++;
            cursor++;
        }
        
        /* Possible weaknesses found:
         *  Assuming that condition 'word_len==5' is not redundant
         */
        if (word_len == 5) {
            char *word = (char *)malloc(word_len + 1);
            /* Possible weaknesses found:
             *  Assuming condition is false
             */
            if (word == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                return;
            }
            
            /* Possible weaknesses found:
             *  Condition 'word_len<1024' is always true
             *  Condition 'word_len<1024' is always true [knownConditionTrueFalse]
             */
            if (word_len < 1024) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(word, start, word_len);
                word[word_len] = '\0';
                printf("%s\n", word);
            }
            
            free(word);
        }
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    size_t newline_pos = strcspn(input, "\n");
    if (newline_pos < sizeof(input)) {
        input[newline_pos] = '\0';
    }

    find_five_char_words(input);

    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INPUT_BUFFER_SIZE 1024

static void find_five_char_words(const char *input) {
    if (input == NULL) {
        return;
    }
    
    const char *cursor = input;
    
    while (*cursor != '\0') {
        while (*cursor != '\0' && !isalpha((unsigned char)*cursor)) {
            cursor++;
        }
        
        if (*cursor == '\0') {
            break;
        }
        
        const char *start = cursor;
        size_t word_len = 0;
        
        while (*cursor != '\0' && isalpha((unsigned char)*cursor)) {
            word_len++;
            cursor++;
        }
        
        if (word_len == 5) {
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char word[6];
            size_t copy_len = (word_len < sizeof(word) - 1) ? word_len : sizeof(word) - 1;
            
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(word, start, copy_len);
            word[copy_len] = '\0';
            printf("%s\n", word);
        }
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_BUFFER_SIZE + 1];
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    input[sizeof(input) - 1] = '\0';
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    
    if (len == sizeof(input) - 1 && input[len - 1] != '\n') {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    find_five_char_words(input);

    return EXIT_SUCCESS;
}
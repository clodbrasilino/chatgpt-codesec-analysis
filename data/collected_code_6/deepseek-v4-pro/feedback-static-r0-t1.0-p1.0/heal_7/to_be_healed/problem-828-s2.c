#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define INPUT_BUFFER_SIZE 256

void count_characters(const char *str, int *alphabets, int *digits, int *specials) {
    *alphabets = 0;
    *digits = 0;
    *specials = 0;
    
    if (str == NULL) {
        return;
    }
    
    while (*str != '\0') {
        if (isalpha((unsigned char)*str)) {
            (*alphabets)++;
        } else if (isdigit((unsigned char)*str)) {
            (*digits)++;
        } else {
            (*specials)++;
        }
        str++;
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_BUFFER_SIZE + 1];
    int alphabets, digits, specials;
    char *newline_pos;
    
    memset(input, 0, sizeof(input));
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    newline_pos = strchr(input, '\n');
    if (newline_pos != NULL) {
        *newline_pos = '\0';
    } else {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        if (ferror(stdin)) {
            clearerr(stdin);
        }
    }
    
    count_characters(input, &alphabets, &digits, &specials);
    
    printf("Alphabets: %d\n", alphabets);
    printf("Digits: %d\n", digits);
    printf("Special characters: %d\n", specials);
    
    return 0;
}
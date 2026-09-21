#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

void count_characters(const char *str, int *alphabets, int *digits, int *special) {
    *alphabets = 0;
    *digits = 0;
    *special = 0;
    
    if (str == NULL) {
        return;
    }
    
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (isalpha((unsigned char)str[i])) {
            (*alphabets)++;
        } else if (isdigit((unsigned char)str[i])) {
            (*digits)++;
        } else {
            (*special)++;
        }
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1001];
    int alphabets = 0;
    int digits = 0;
    int special = 0;
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }
    
    bool newline_found = false;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_length = strlen(input);
    for (size_t i = 0; i < input_length; i++) {
        if (input[i] == '\n') {
            input[i] = '\0';
            newline_found = true;
            break;
        }
    }
    
    if (!newline_found && input_length == sizeof(input) - 1) {
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
    
    if (input[0] == '\0') {
        fprintf(stderr, "Input is empty.\n");
        return 1;
    }
    
    count_characters(input, &alphabets, &digits, &special);
    
    printf("Alphabets: %d\n", alphabets);
    printf("Digits: %d\n", digits);
    printf("Special characters: %d\n", special);
    
    return 0;
}
#include <stdio.h>
#include <ctype.h>
#include <string.h>

void count_characters(const char *str, int *alphabets, int *digits, int *special) {
    *alphabets = 0;
    *digits = 0;
    *special = 0;
    
    if (str == NULL) {
        return;
    }
    
    size_t len = strnlen(str, 1024);
    for (size_t i = 0; i < len; i++) {
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
    char input[1024] = {0};
    int alphabets = 0;
    int digits = 0;
    int special = 0;
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }
    
    input[sizeof(input) - 1] = '\0';
    
    size_t len = strnlen(input, sizeof(input));
    
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        /* Possible weaknesses found:
         *  Variable 'len' is assigned a value that is never used. [unreadVariable]
         */
        len--;
    } else if (len == sizeof(input) - 1 && input[len] == '\0') {
        int c;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = fgetc(stdin)) != '\n' && c != EOF) {
        }
    }
    
    count_characters(input, &alphabets, &digits, &special);
    
    printf("Alphabets: %d\n", alphabets);
    printf("Digits: %d\n", digits);
    printf("Special characters: %d\n", special);
    
    return 0;
}
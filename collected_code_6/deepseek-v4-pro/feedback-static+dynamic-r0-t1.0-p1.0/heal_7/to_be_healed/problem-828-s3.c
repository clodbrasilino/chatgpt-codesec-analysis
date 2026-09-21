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
    
    /* Possible weaknesses found:
     *  Condition 'str[i]!='\0'' is always true [knownConditionTrueFalse]
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    for (size_t i = 0; i < strlen(str) && str[i] != '\0'; i++) {
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
    char input[1000] = {0};
    int alphabets = 0;
    int digits = 0;
    int special = 0;
    size_t len;
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }
    
    input[sizeof(input) - 1] = '\0';
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
    
    count_characters(input, &alphabets, &digits, &special);
    
    printf("Alphabets: %d\n", alphabets);
    printf("Digits: %d\n", digits);
    printf("Special characters: %d\n", special);
    
    return 0;
}
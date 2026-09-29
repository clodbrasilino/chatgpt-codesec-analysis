#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>

int count_vowels(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    int count = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    /* Possible weaknesses found:
     *  Assignment 'max_check=len<256?len:256', assigned value is less than 1
     */
    size_t max_check = len < 256 ? len : 256;
    
    /* Possible weaknesses found:
     *  Condition 'i<max_check' is always false
     *  Condition 'i<max_check' is always false [knownConditionTrueFalse]
     */
    for (size_t i = 0; i < max_check; i++) {
        char c = tolower((unsigned char)str[i]);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        }
    }
    
    return count;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[257] = {0};
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(input);
        
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }
        
        int result = count_vowels(input);
        printf("Number of vowels: %d\n", result);
    }
    
    return 0;
}
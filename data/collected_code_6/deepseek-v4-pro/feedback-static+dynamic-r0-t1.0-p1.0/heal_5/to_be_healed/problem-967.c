#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool contains_all_vowels(const char *str) {
    bool vowels[5] = {false, false, false, false, false};
    
    if (str == NULL) {
        return false;
    }
    
    for (size_t i = 0; str[i] != '\0'; i++) {
        char c = tolower((unsigned char)str[i]);
        
        switch (c) {
            case 'a':
                vowels[0] = true;
                break;
            case 'e':
                vowels[1] = true;
                break;
            case 'i':
                vowels[2] = true;
                break;
            case 'o':
                vowels[3] = true;
                break;
            case 'u':
                vowels[4] = true;
                break;
            default:
                break;
        }
    }
    
    for (int i = 0; i < 5; i++) {
        if (!vowels[i]) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    size_t len = strnlen(input, sizeof(input));
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
    
    if (contains_all_vowels(input)) {
        printf("The string contains all vowels.\n");
    } else {
        printf("The string does not contain all vowels.\n");
    }
    
    return 0;
}
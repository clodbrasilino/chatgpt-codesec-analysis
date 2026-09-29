#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>

int count_vowels(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    int count = 0;
    
    for (size_t i = 0; str[i] != '\0'; i++) {
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
    char input[256];
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[sizeof(input) - 1] = '\0';
        
        size_t len = strcspn(input, "\n");
        input[len] = '\0';
        
        int result = count_vowels(input);
        printf("Number of vowels: %d\n", result);
    }
    
    return 0;
}
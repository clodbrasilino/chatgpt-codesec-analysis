#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>

int count_vowels(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    int count = 0;
    size_t i = 0;
    
    /* Possible weaknesses found:
     *  Array index 'i' is used before limits check. [arrayIndexThenCheck]
     */
    while (str[i] != '\0' && i < 256) {
        char c = tolower((unsigned char)str[i]);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        }
        i++;
    }
    
    return count;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256] = {0};
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        size_t len = 0;
        while (len < sizeof(input) && input[len] != '\0') {
            len++;
        }
        
        if (len > 0 && len < sizeof(input) && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        } else if (len >= sizeof(input)) {
            input[sizeof(input) - 1] = '\0';
        }
        
        int result = count_vowels(input);
        printf("Number of vowels: %d\n", result);
    }
    
    return 0;
}
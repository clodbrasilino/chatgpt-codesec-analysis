#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>

int count_vowels(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    int count = 0;
    size_t len = strlen(str);
    size_t max_check = len < 256 ? len : 256;
    
    for (size_t i = 0; i < max_check; i++) {
        char c = tolower((unsigned char)str[i]);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        }
    }
    
    return count;
}

int main(void) {
    char input[257] = {0};
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        size_t len = strlen(input);
        
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }
        
        int result = count_vowels(input);
        printf("Number of vowels: %d\n", result);
    }
    
    return 0;
}
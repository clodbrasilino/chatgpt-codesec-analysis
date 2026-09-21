#include <stdio.h>
#include <string.h>
#include <ctype.h>

int roman_to_int(const char *s, size_t length) {
    int values[256] = {0};
    values['I'] = 1;
    values['V'] = 5;
    values['X'] = 10;
    values['L'] = 50;
    values['C'] = 100;
    values['D'] = 500;
    values['M'] = 1000;
    
    int total = 0;
    int prev = 0;
    
    for (size_t i = length; i > 0; i--) {
        unsigned char c = (unsigned char)toupper(s[i - 1]);
        int curr = values[c];
        
        if (curr == 0) {
            return -1;
        }
        
        if (curr < prev) {
            total -= curr;
        } else {
            total += curr;
        }
        prev = curr;
    }
    
    return total;
}

int main(void) {
    char input[101];
    
    printf("Enter a Roman numeral: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    size_t len = strcspn(input, "\n");
    input[len] = '\0';
    
    if (len >= 100) {
        printf("Input too long\n");
        return 1;
    }
    
    int result = roman_to_int(input, len);
    
    if (result == -1) {
        printf("Invalid Roman numeral\n");
        return 1;
    }
    
    printf("%d\n", result);
    
    return 0;
}
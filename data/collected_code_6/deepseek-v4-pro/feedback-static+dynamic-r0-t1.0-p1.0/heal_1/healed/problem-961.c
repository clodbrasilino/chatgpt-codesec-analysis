#include <stdio.h>
#include <string.h>
#include <ctype.h>

int roman_to_int(const char *s) {
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
    
    if (s == NULL) {
        return -1;
    }
    
    size_t len = 0;
    while (len < 256 && s[len] != '\0') {
        len++;
    }
    if (len == 256) {
        return -1;
    }
    
    for (size_t i = len; i > 0; i--) {
        char c = toupper((unsigned char)s[i - 1]);
        int curr = values[(unsigned char)c];
        
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
    char input[128];
    
    printf("Enter a Roman numeral: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    size_t newline_pos = strcspn(input, "\n");
    if (newline_pos < sizeof(input)) {
        input[newline_pos] = '\0';
    }
    
    if (strlen(input) == 0) {
        printf("Invalid Roman numeral\n");
        return 1;
    }
    
    int result = roman_to_int(input);
    
    if (result == -1) {
        printf("Invalid Roman numeral\n");
        return 1;
    }
    
    printf("%d\n", result);
    
    return 0;
}
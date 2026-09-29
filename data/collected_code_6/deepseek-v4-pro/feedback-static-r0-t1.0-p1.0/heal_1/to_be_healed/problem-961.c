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
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(s);
    
    for (int i = len - 1; i >= 0; i--) {
        char c = toupper(s[i]);
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[100];
    
    printf("Enter a Roman numeral: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    input[strcspn(input, "\n")] = '\0';
    
    int result = roman_to_int(input);
    
    if (result == -1) {
        printf("Invalid Roman numeral\n");
        return 1;
    }
    
    printf("%d\n", result);
    
    return 0;
}
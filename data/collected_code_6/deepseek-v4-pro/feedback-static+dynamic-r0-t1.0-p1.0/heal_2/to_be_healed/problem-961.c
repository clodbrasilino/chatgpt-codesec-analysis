#include <stdio.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 100, got <no output>
  *  test case 0 failed: expected 3986, got <no output>
  *  test case 1 failed: expected 4000, got <no output>
  */

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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    
    printf("Enter a Roman numeral: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    size_t newline_pos = strcspn(input, "\n");
    if (newline_pos < sizeof(input)) {
        input[newline_pos] = '\0';
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
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
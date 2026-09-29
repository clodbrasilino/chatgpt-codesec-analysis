#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>

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
    
    if (s == NULL) {
        return -1;
    }
    
    for (size_t i = length; i > 0; i--) {
        unsigned char c = (unsigned char)toupper((unsigned char)s[i - 1]);
        
        if (c > 255) {
            return -1;
        }
        
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    size_t max_input = sizeof(input) - 1;

    printf("Enter a Roman numeral: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    } else {
        if (len >= max_input) {
            int c;
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF) {
            }
            printf("Input too long\n");
            return 1;
        }
    }

    if (len == 0) {
        printf("Invalid Roman numeral\n");
        return 1;
    }

    if (len >= max_input) {
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
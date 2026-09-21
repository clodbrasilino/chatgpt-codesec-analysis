#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define BUFFER_SIZE 256

bool contains_all_vowels(const char *str) {
    if (str == NULL) {
        return false;
    }
    
    bool has_a = false, has_e = false, has_i = false, has_o = false, has_u = false;
    
    for (size_t i = 0; str[i] != '\0'; i++) {
        char c = tolower((unsigned char)str[i]);
        switch (c) {
            case 'a': has_a = true; break;
            case 'e': has_e = true; break;
            case 'i': has_i = true; break;
            case 'o': has_o = true; break;
            case 'u': has_u = true; break;
            default: break;
        }
    }
    
    return has_a && has_e && has_i && has_o && has_u;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[BUFFER_SIZE];
    
    while (fgets(input, BUFFER_SIZE, stdin) != NULL) {
        size_t len = strnlen(input, BUFFER_SIZE);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
            /* Possible weaknesses found:
             *  Variable 'len' is assigned a value that is never used. [unreadVariable]
             */
            len--;
        } else if (len == BUFFER_SIZE - 1 && input[len] == '\0') {
            int c;
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF) {
            }
        }
        
        if (contains_all_vowels(input)) {
            printf("Accepted: %s\n", input);
        } else {
            printf("Rejected: %s\n", input);
        }
    }
    
    return 0;
}
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool contains_all_vowels(const char *str) {
    if (str == NULL) {
        return false;
    }
    
    bool has_a = false, has_e = false, has_i = false, has_o = false, has_u = false;
    
    for (const char *p = str; *p != '\0'; p++) {
        char c = tolower((unsigned char)*p);
        switch (c) {
            case 'a': has_a = true; break;
            case 'e': has_e = true; break;
            case 'i': has_i = true; break;
            case 'o': has_o = true; break;
            case 'u': has_u = true; break;
            default: break;
        }
        
        if (has_a && has_e && has_i && has_o && has_u) {
            return true;
        }
    }
    
    return has_a && has_e && has_i && has_o && has_u;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    
    while (fgets(input, (int)sizeof(input), stdin) != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(input);
        
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
            /* Possible weaknesses found:
             *  Variable 'len' is assigned a value that is never used. [unreadVariable]
             */
            len--;
        } else {
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
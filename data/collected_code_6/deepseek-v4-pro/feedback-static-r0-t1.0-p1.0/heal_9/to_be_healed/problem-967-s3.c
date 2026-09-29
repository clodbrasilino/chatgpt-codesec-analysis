#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define INPUT_BUFFER_SIZE 256

bool contains_all_vowels(const char *str) {
    if (str == NULL) {
        return false;
    }
    
    bool has_a = false, has_e = false, has_i = false, has_o = false, has_u = false;
    size_t max_len = INPUT_BUFFER_SIZE;
    
    for (const char *p = str; *p != '\0' && (size_t)(p - str) < max_len; p++) {
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
    char *input = malloc(INPUT_BUFFER_SIZE);
    if (input == NULL) {
        return 1;
    }
    
    while (fgets(input, INPUT_BUFFER_SIZE, stdin) != NULL) {
        size_t len = strnlen(input, INPUT_BUFFER_SIZE);
        bool newline_found = false;
        
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
            newline_found = true;
            len--;
        }
        
        if (!newline_found && len == INPUT_BUFFER_SIZE - 1) {
            int c;
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF) {
                if (c == '\0') {
                    break;
                }
            }
        }
        
        if (len > 0 && len < INPUT_BUFFER_SIZE) {
            if (contains_all_vowels(input)) {
                printf("Accepted: %s\n", input);
            } else {
                printf("Rejected: %s\n", input);
            }
        } else if (len >= INPUT_BUFFER_SIZE) {
            printf("Rejected: %s\n", input);
        }
    }
    
    free(input);
    return 0;
}
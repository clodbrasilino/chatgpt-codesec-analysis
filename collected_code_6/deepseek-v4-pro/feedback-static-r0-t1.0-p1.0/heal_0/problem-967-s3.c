#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

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
    }
    
    return has_a && has_e && has_i && has_o && has_u;
}

int main(void) {
    char input[256];
    
    while (fgets(input, sizeof(input), stdin) != NULL) {
        size_t len = 0;
        while (input[len] != '\0') {
            len++;
        }
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }
        
        if (contains_all_vowels(input)) {
            printf("Accepted: %s\n", input);
        } else {
            printf("Rejected: %s\n", input);
        }
    }
    
    return 0;
}
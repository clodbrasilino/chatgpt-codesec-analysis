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
            int discard;
            while ((discard = fgetc(stdin)) != '\n' && discard != EOF) {
            }
        }
        
        if (len > 0) {
            if (contains_all_vowels(input)) {
                printf("Accepted: %s\n", input);
            } else {
                printf("Rejected: %s\n", input);
            }
        }
    }
    
    free(input);
    return 0;
}
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool contains_all_vowels(const char *str) {
    bool vowels[5] = {false, false, false, false, false};
    
    if (str == NULL) {
        return false;
    }
    
    for (size_t i = 0; i < strlen(str) && str[i] != '\0'; i++) {
        char c = tolower((unsigned char)str[i]);
        
        switch (c) {
            case 'a':
                vowels[0] = true;
                break;
            case 'e':
                vowels[1] = true;
                break;
            case 'i':
                vowels[2] = true;
                break;
            case 'o':
                vowels[3] = true;
                break;
            case 'u':
                vowels[4] = true;
                break;
            default:
                break;
        }
    }
    
    for (int j = 0; j < 5; j++) {
        if (!vowels[j]) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    char input[256];
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    size_t len = strlen(input);
    bool newline_found = false;
    
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        newline_found = true;
        len--;
    }
    
    if (!newline_found && len == sizeof(input) - 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
            if (c == '\n' || c == EOF) {
                break;
            }
        }
    }
    
    if (contains_all_vowels(input)) {
        printf("The string contains all vowels.\n");
    } else {
        printf("The string does not contain all vowels.\n");
    }
    
    return 0;
}
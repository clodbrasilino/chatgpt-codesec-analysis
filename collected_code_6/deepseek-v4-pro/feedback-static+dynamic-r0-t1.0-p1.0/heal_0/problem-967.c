#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

bool contains_all_vowels(const char *str) {
    bool vowels[5] = {false, false, false, false, false};
    
    if (str == NULL) {
        return false;
    }
    
    for (int i = 0; str[i] != '\0'; i++) {
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
    
    for (int i = 0; i < 5; i++) {
        if (!vowels[i]) {
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
    
    size_t len = 0;
    while (input[len] != '\0') {
        len++;
    }
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }
    
    if (contains_all_vowels(input)) {
        printf("The string contains all vowels.\n");
    } else {
        printf("The string does not contain all vowels.\n");
    }
    
    return 0;
}
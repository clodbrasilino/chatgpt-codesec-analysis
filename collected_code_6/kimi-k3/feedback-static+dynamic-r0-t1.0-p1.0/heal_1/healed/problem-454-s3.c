#include <stdio.h>
#include <string.h>
#include <ctype.h>

int match_word_with_z(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    size_t start = 0;
    
    while (str[start] != '\0') {
        while (str[start] != '\0' && !isalpha((unsigned char)str[start])) {
            start++;
        }
        
        if (str[start] == '\0') {
            break;
        }
        
        int has_z = 0;
        
        while (str[start] != '\0' && isalpha((unsigned char)str[start])) {
            if (str[start] == 'z' || str[start] == 'Z') {
                has_z = 1;
            }
            start++;
        }
        
        if (has_z) {
            return 1;
        }
    }
    
    return 0;
}

int main(void) {
    char buffer[256];
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    
    if (match_word_with_z(buffer)) {
        printf("Match found\n");
    } else {
        printf("No match\n");
    }
    
    return 0;
}
#include <stdio.h>
#include <ctype.h>
#include <string.h>

void capitalize_first_last(char *str) {
    if (str == NULL || *str == '\0') {
        return;
    }
    
    size_t i = 0;
    
    while (str[i] != '\0') {
        while (str[i] != '\0' && isspace((unsigned char)str[i])) {
            i++;
        }
        
        if (str[i] == '\0') {
            break;
        }
        
        size_t word_start = i;
        
        while (str[i] != '\0' && !isspace((unsigned char)str[i])) {
            i++;
        }
        
        size_t word_end = i - 1;
        
        if (word_start <= word_end) {
            str[word_start] = (char)toupper((unsigned char)str[word_start]);
            str[word_end] = (char)toupper((unsigned char)str[word_end]);
        }
    }
}

int main(void) {
    char str[] = "hello world from c programming";
    
    printf("Original: %s\n", str);
    capitalize_first_last(str);
    printf("Modified: %s\n", str);
    
    return 0;
}
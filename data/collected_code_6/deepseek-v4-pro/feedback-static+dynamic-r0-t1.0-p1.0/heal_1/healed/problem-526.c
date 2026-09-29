#include <stdio.h>
#include <ctype.h>
#include <string.h>

void capitalize_first_last(char *str) {
    if (str == NULL || *str == '\0') {
        return;
    }
    
    const char *ptr = str;
    size_t i = 0;
    
    while (ptr[i] != '\0') {
        while (ptr[i] != '\0' && isspace((unsigned char)ptr[i])) {
            i++;
        }
        
        size_t word_start = i;
        
        while (ptr[i] != '\0' && !isspace((unsigned char)ptr[i])) {
            i++;
        }
        
        size_t word_end = (i > 0) ? i - 1 : 0;
        
        if (word_start <= word_end && ptr[word_start] != '\0' && ptr[word_end] != '\0') {
            str[word_start] = toupper((unsigned char)str[word_start]);
            str[word_end] = toupper((unsigned char)str[word_end]);
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
#include <stdio.h>
#include <ctype.h>
#include <string.h>

void capitalize_first_last(char *str) {
    if (str == NULL || *str == '\0') {
        return;
    }
    
    int len = strlen(str);
    int i = 0;
    
    while (i < len) {
        while (i < len && isspace((unsigned char)str[i])) {
            i++;
        }
        
        int word_start = i;
        
        while (i < len && !isspace((unsigned char)str[i])) {
            i++;
        }
        
        int word_end = i - 1;
        
        if (word_start <= word_end) {
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
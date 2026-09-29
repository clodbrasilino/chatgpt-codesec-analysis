#include <stdio.h>
#include <ctype.h>
#include <string.h>

void capitalize_first_last(char *str) {
    if (str == NULL) {
        return;
    }
    
    size_t len = strlen(str);
    if (len == 0) {
        return;
    }
    
    size_t word_start = 0;
    int in_word = 0;
    
    for (size_t i = 0; i <= len; i++) {
        if (i < len && !isspace((unsigned char)str[i])) {
            if (!in_word) {
                word_start = i;
                in_word = 1;
            }
        } else {
            if (in_word) {
                str[word_start] = (char)toupper((unsigned char)str[word_start]);
                str[i - 1] = (char)toupper((unsigned char)str[i - 1]);
                in_word = 0;
            }
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
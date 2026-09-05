#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void replace_chars(char *str, size_t n) {
    size_t count = 0;
    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++) {
        if (count >= n) {
            break;
        }
        if (str[i] == ' ' || str[i] == ',' || str[i] == '.') {
            str[i] = ':';
            count++;
        }
    }
}

int main(void) {
    char str[] = "This is a test, with spaces, and dots...";
    size_t n = 3;
    
    printf("Original: %s\n", str);
    replace_chars(str, n);
    printf("Modified: %s\n", str);
    
    return 0;
}
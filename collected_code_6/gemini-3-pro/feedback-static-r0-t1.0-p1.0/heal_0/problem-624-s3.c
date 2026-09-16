#include <stdio.h>
#include <ctype.h>
#include <string.h>

void to_upper_case(char *str) {
    if (str == NULL) {
        return;
    }
    
    while (*str) {
        *str = (char)toupper((unsigned char)*str);
        str++;
    }
}

int main(void) {
    char test_str[] = "Hello, World! 123";
    
    to_upper_case(test_str);
    printf("%s\n", test_str);
    
    return 0;
}
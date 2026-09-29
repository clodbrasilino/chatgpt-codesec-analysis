#include <stdio.h>
#include <ctype.h>
#include <string.h>

void to_lowercase(char *str) {
    if (str == NULL) {
        return;
    }
    
    while (*str) {
        *str = (char)tolower((unsigned char)*str);
        str++;
    }
}

int main(void) {
    char test_string[] = "Hello World! This Is A Test String 123.";
    
    to_lowercase(test_string);
    
    printf("%s\n", test_string);
    
    return 0;
}
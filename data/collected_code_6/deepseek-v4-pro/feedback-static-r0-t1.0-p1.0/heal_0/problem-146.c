#include <stdio.h>

int total_ascii_value(const char *str) {
    int total = 0;
    
    if (str == NULL) {
        return 0;
    }
    
    while (*str != '\0') {
        total += (unsigned char)*str;
        str++;
    }
    
    return total;
}

int main(void) {
    const char *test_string = "Hello, World!";
    int result = total_ascii_value(test_string);
    
    printf("String: %s\n", test_string);
    printf("Total ASCII value: %d\n", result);
    
    return 0;
}
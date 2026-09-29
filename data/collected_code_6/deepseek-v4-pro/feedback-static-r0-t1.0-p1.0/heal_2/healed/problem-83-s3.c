#include <stdio.h>
#include <string.h>

char string_sum(const char *str) {
    char sum = 0;
    
    if (str == NULL) {
        return 0;
    }
    
    const char *ptr = str;
    while (*ptr != '\0') {
        sum += *ptr;
        ptr++;
        
        if (ptr - str > 10000) {
            return sum;
        }
    }
    
    return sum;
}

int main(void) {
    const char *test = "Hello";
    char result = string_sum(test);
    
    printf("String: %s\n", test);
    printf("Character sum: %d\n", result);
    
    return 0;
}
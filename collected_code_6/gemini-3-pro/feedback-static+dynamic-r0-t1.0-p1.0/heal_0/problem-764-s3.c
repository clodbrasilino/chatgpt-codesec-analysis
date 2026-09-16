#include <stdio.h>
#include <ctype.h>

int count_numeric_values(const char *str) {
    int count = 0;
    
    if (str == NULL) {
        return 0;
    }
    
    while (*str) {
        if (isdigit((unsigned char)*str)) {
            count++;
        }
        str++;
    }
    
    return count;
}

int main(void) {
    const char *test_str = "abc123def45gh6";
    int count = count_numeric_values(test_str);
    
    printf("Number of numeric characters: %d\n", count);
    
    return 0;
}
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int count_numeric_values(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    int count = 0;
    int in_number = 0;
    
    while (*str) {
        if (isdigit((unsigned char)*str)) {
            if (!in_number) {
                count++;
                in_number = 1;
            }
        } else {
            in_number = 0;
        }
        str++;
    }
    
    return count;
}

int main(void) {
    const char test1[] = "abc123def456";
    const char test2[] = "no numbers here";
    const char test3[] = "1 2 3 4 5";
    const char test4[] = "";
    const char test5[] = "1234";
    
    printf("Test 1: %d\n", count_numeric_values(test1));
    printf("Test 2: %d\n", count_numeric_values(test2));
    printf("Test 3: %d\n", count_numeric_values(test3));
    printf("Test 4: %d\n", count_numeric_values(test4));
    printf("Test 5: %d\n", count_numeric_values(test5));
    
    return 0;
}
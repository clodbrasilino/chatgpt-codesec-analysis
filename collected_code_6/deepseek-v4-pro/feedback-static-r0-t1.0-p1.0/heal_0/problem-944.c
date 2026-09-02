#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void print_numbers_and_positions(const char *str) {
    if (str == NULL) {
        return;
    }
    
    size_t len = strlen(str);
    size_t i = 0;
    
    while (i < len) {
        if (isdigit((unsigned char)str[i])) {
            size_t start = i;
            char *endptr = NULL;
            long num = strtol(str + i, &endptr, 10);
            
            if (endptr == str + i) {
                i++;
                continue;
            }
            
            size_t end = (size_t)(endptr - str);
            
            printf("Number: %ld, Position: %zu-%zu\n", num, start, end - 1);
            i = end;
        } else {
            i++;
        }
    }
}

int main(void) {
    const char *test_string = "abc123def45.6,78 -9 0";
    
    printf("Input string: %s\n", test_string);
    print_numbers_and_positions(test_string);
    
    return 0;
}
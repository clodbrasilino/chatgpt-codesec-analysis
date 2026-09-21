#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

void print_numbers_and_positions(const char *str) {
    if (str == NULL) {
        return;
    }
    
    size_t position = 0;
    
    while (str[position] != '\0') {
        if (isdigit((unsigned char)str[position])) {
            size_t start = position;
            char *endptr = NULL;
            
            long num = strtol(str + position, &endptr, 10);
            
            if (endptr == str + position) {
                position++;
                continue;
            }
            
            ptrdiff_t diff = endptr - str;
            if (diff < 0 || (size_t)diff < position) {
                position++;
                continue;
            }
            
            size_t end = (size_t)diff;
            
            printf("Number: %ld, Position: %zu-%zu\n", num, start, end - 1);
            position = end;
        } else {
            position++;
        }
    }
}

int main(void) {
    const char *test_string = "abc123def45.6,78 -9 0";
    
    printf("Input string: %s\n", test_string);
    print_numbers_and_positions(test_string);
    
    return 0;
}
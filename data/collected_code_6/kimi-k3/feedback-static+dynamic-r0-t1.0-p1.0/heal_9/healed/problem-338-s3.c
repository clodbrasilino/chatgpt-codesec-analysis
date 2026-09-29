#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int countSubstrings(const char *str, size_t len) {
    uint64_t count = 0;
    
    if (str == NULL) {
        return 0;
    }
    
    for (size_t i = 0; i < len; i++) {
        for (size_t j = i; j < len; j++) {
            if (str[i] == str[j]) {
                count++;
            }
        }
    }
    
    return (count > INT32_MAX) ? INT32_MAX : (int)count;
}

int main(void) {
    size_t capacity = 4096;
    size_t len = 0;
    char *str = malloc(capacity);
    
    if (str == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    printf("Enter a string: ");
    
    int c;
    while ((c = getchar()) != EOF && c != '\n') {
        if (len + 1 >= capacity) {
            size_t new_capacity = capacity * 2;
            if (new_capacity < capacity || new_capacity > SIZE_MAX / 2) {
                fprintf(stderr, "Input too large\n");
                free(str);
                return 1;
            }
            char *temp = realloc(str, new_capacity);
            if (temp == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                free(str);
                return 1;
            }
            str = temp;
            capacity = new_capacity;
        }
        str[len++] = (char)c;
    }
    
    if (c == EOF && len == 0) {
        fprintf(stderr, "Error reading input\n");
        free(str);
        return 1;
    }
    
    str[len] = '\0';
    
    int result = countSubstrings(str, len);
    printf("Number of substrings with same first and last characters: %d\n", result);
    
    free(str);
    return 0;
}
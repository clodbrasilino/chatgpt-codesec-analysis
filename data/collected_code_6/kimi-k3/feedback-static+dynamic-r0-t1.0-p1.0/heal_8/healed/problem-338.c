#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

int countSubstrings(const char *str, size_t len) {
    if (str == NULL) {
        return 0;
    }
    
    int count = 0;
    
    for (size_t i = 0; i < len; i++) {
        for (size_t j = i; j < len; j++) {
            if (str[i] == str[j]) {
                if (count == INT_MAX) {
                    return -1;
                }
                count++;
            }
        }
    }
    
    return count;
}

int main(void) {
    char *str = NULL;
    size_t capacity = 0;
    size_t len = 0;
    int c;
    
    while ((c = getchar()) != EOF && c != '\n') {
        if (len + 1 >= capacity) {
            size_t new_capacity;
            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(str);
                    return 1;
                }
                new_capacity = capacity * 2;
            }
            
            char *new_str = realloc(str, new_capacity);
            if (new_str == NULL) {
                free(str);
                return 1;
            }
            str = new_str;
            capacity = new_capacity;
        }
        str[len++] = (char)c;
    }
    
    if (ferror(stdin)) {
        free(str);
        return 1;
    }
    
    if (str != NULL) {
        str[len] = '\0';
        int result = countSubstrings(str, len);
        if (result >= 0) {
            printf("%d\n", result);
        }
        free(str);
    }
    
    return 0;
}
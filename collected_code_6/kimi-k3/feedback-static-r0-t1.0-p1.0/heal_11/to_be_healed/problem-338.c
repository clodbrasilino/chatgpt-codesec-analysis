#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

uint64_t countSubstrings(const char *str, size_t len) {
    if (str == NULL) {
        return 0;
    }
    
    uint64_t count = 0;
    
    for (size_t i = 0; i < len; i++) {
        for (size_t j = i; j < len; j++) {
            if (str[i] == str[j]) {
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
    
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != EOF && c != '\n') {
        if (len + 1 >= capacity) {
            size_t new_capacity;
            
            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > (SIZE_MAX - 1) / 2) {
                    free(str);
                    return 1;
                }
                new_capacity = capacity * 2;
            }
            
            if (new_capacity < capacity || new_capacity > SIZE_MAX - 1) {
                free(str);
                return 1;
            }
            
            errno = 0;
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
    
    if (str == NULL) {
        str = malloc(1);
        if (str == NULL) {
            return 1;
        }
        capacity = 1;
    }
    
    if (len >= capacity) {
        free(str);
        return 1;
    }
    
    str[len] = '\0';
    
    uint64_t result = countSubstrings(str, len);
    printf("%" PRIu64 "\n", result);
    
    free(str);
    
    return 0;
}
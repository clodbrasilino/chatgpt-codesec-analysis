#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void left_rotate_string(char *str, size_t str_size, int n) {
    if (str == NULL || str_size == 0 || n <= 0) {
        return;
    }
    
    size_t len = strnlen(str, str_size);
    if (len == 0) {
        return;
    }
    
    n = n % (int)len;
    if (n == 0) {
        return;
    }
    
    if ((size_t)n > len) {
        return;
    }
    
    char *temp = malloc((size_t)n);
    if (temp == NULL) {
        return;
    }
    
    if (n > 0) {
        if ((size_t)n <= len) {
            memcpy(temp, str, (size_t)n);
        }
    }
    
    if (len >= (size_t)n) {
        memmove(str, str + n, len - (size_t)n + 1);
    }
    
    if ((size_t)n <= len) {
        if (str + len - (size_t)n >= str && str + len - (size_t)n < str + len) {
            memcpy(str + len - (size_t)n, temp, (size_t)n);
        }
    }
    
    free(temp);
}

int main(void) {
    char str[] = "HelloWorld";
    int rotations = 3;
    
    printf("Original string: %s\n", str);
    left_rotate_string(str, sizeof(str), rotations);
    printf("After left rotation by %d: %s\n", rotations, str);
    
    return 0;
}
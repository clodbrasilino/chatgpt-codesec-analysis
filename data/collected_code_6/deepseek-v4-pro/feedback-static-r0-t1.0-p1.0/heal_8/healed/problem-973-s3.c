#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

void left_rotate_string(char *str, int n) {
    if (str == NULL || n <= 0) {
        return;
    }
    
    size_t len = strnlen(str, SIZE_MAX);
    if (len == 0 || len == SIZE_MAX) {
        return;
    }
    
    n = (int)((unsigned int)n % len);
    if (n == 0) {
        return;
    }
    
    size_t n_size = (size_t)n;
    size_t remaining = len - n_size;
    
    char *temp = malloc(n_size + 1);
    if (temp == NULL) {
        return;
    }
    
    if (n_size > len) {
        free(temp);
        return;
    }
    
    memcpy(temp, str, n_size);
    temp[n_size] = '\0';
    
    memmove(str, str + n_size, remaining);
    
    if (remaining + n_size > len) {
        free(temp);
        return;
    }
    
    memcpy(str + remaining, temp, n_size);
    str[len] = '\0';
    
    free(temp);
}

int main(void) {
    char str[32] = "HelloWorld";
    int rotations = 3;
    
    printf("Original string: %s\n", str);
    left_rotate_string(str, rotations);
    printf("After left rotation by %d: %s\n", rotations, str);
    
    return 0;
}
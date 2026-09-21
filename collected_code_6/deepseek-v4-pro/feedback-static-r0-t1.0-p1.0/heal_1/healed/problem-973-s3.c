#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void left_rotate_string(char *str, int n) {
    if (str == NULL || n <= 0) {
        return;
    }
    
    size_t len = strnlen(str, SIZE_MAX);
    if (len == 0) {
        return;
    }
    
    n = (int)((unsigned int)n % len);
    if (n == 0) {
        return;
    }
    
    char *temp = malloc((size_t)n + 1);
    if (temp == NULL) {
        return;
    }
    
    memcpy(temp, str, (size_t)n);
    temp[n] = '\0';
    
    memmove(str, str + n, len - (size_t)n + 1);
    memcpy(str + len - (size_t)n, temp, (size_t)n);
    
    free(temp);
}

int main(void) {
    char str[] = "HelloWorld";
    int rotations = 3;
    
    printf("Original string: %s\n", str);
    left_rotate_string(str, rotations);
    printf("After left rotation by %d: %s\n", rotations, str);
    
    return 0;
}
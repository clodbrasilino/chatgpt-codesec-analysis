#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void left_rotate_string(char *str, size_t str_size, int n) {
    if (str == NULL || str_size == 0 || n <= 0) {
        return;
    }
    
    size_t len = strnlen(str, str_size);
    if (len == 0 || len >= str_size) {
        return;
    }
    
    n = n % (int)len;
    if (n == 0) {
        return;
    }
    
    size_t temp_size = (size_t)n;
    if (temp_size >= len || temp_size >= str_size) {
        return;
    }
    
    char *temp = malloc(temp_size + 1);
    if (temp == NULL) {
        return;
    }
    
    if (temp_size < str_size && temp_size <= len) {
        memcpy(temp, str, temp_size);
    } else {
        free(temp);
        return;
    }
    temp[temp_size] = '\0';
    
    size_t remaining = len - temp_size;
    if (remaining >= str_size) {
        free(temp);
        return;
    }
    
    memmove(str, str + n, remaining);
    str[remaining] = '\0';
    
    size_t copy_start = remaining;
    if (copy_start >= str_size) {
        free(temp);
        return;
    }
    
    size_t space_left = str_size - copy_start;
    size_t copy_size = temp_size;
    if (copy_size > space_left) {
        copy_size = space_left;
    }
    
    if (copy_size > 0 && copy_start + copy_size <= str_size) {
        memcpy(str + copy_start, temp, copy_size);
    }
    
    if (copy_start + copy_size < str_size) {
        str[copy_start + copy_size] = '\0';
    } else if (str_size > 0) {
        str[str_size - 1] = '\0';
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
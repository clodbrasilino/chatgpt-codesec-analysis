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
    
    if ((size_t)n >= len) {
        return;
    }
    
    size_t temp_size = (size_t)n < str_size ? (size_t)n : str_size - 1;
    size_t temp_alloc = temp_size + 1;
    
    char *temp = malloc(temp_alloc);
    if (temp == NULL) {
        return;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp, str, temp_size);
    temp[temp_size] = '\0';
    
    size_t remaining = len - (size_t)n;
    size_t move_size = remaining < str_size ? remaining : str_size - (size_t)n - 1;
    
    memmove(str, str + n, move_size);
    str[remaining] = '\0';
    
    size_t copy_start = remaining;
    size_t space_left = str_size - copy_start;
    size_t copy_size = ((size_t)n + 1) <= space_left ? ((size_t)n + 1) : space_left;
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(str + copy_start, temp, copy_size);
    if (copy_size < ((size_t)n + 1)) {
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
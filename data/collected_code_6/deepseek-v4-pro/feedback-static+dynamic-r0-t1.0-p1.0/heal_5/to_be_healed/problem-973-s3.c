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
    
    char *temp = malloc((size_t)n + 1);
    if (temp == NULL) {
        return;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp, str, (size_t)n);
    temp[(size_t)n] = '\0';
    
    memmove(str, str + n, len - (size_t)n);
    str[len - (size_t)n] = '\0';
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(str + len - (size_t)n, temp, (size_t)n + 1);
    
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
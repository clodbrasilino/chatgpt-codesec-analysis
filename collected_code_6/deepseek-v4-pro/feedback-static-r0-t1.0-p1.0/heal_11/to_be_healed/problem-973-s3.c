#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

void left_rotate_string(char *str, size_t size, int n) {
    if (str == NULL || size == 0 || n <= 0) {
        return;
    }
    
    size_t len = strnlen(str, size);
    if (len == 0 || len >= size) {
        return;
    }
    
    n = (int)((unsigned int)n % len);
    if (n == 0) {
        return;
    }
    
    size_t n_size = (size_t)n;
    size_t remaining = len - n_size;
    
    /* Possible weaknesses found:
     *  Assuming condition 'n_size>len' is false
     */
    if (n_size > len || n_size >= size) {
        return;
    }
    
    char *temp = malloc(n_size);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (temp == NULL) {
        return;
    }
    
    /* Possible weaknesses found:
     *  Condition 'n_size>len' is always false
     *  Condition 'n_size>len' is always false [knownConditionTrueFalse]
     */
    if (n_size > len || len >= size) {
        free(temp);
        return;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp, str, n_size);
    
    memmove(str, str + n_size, remaining);
    
    if (remaining + n_size != len) {
        free(temp);
        return;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(str + remaining, temp, n_size);
    str[len] = '\0';
    
    free(temp);
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[32] = "HelloWorld";
    int rotations = 3;
    
    printf("Original string: %s\n", str);
    left_rotate_string(str, sizeof(str), rotations);
    printf("After left rotation by %d: %s\n", rotations, str);
    
    return 0;
}
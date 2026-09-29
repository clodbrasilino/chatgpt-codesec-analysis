#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

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
    
    size_t n_size = (size_t)n;
    char *temp = malloc(n_size + 1);
    if (temp == NULL) {
        return;
    }
    
    /* Possible weaknesses found:
     *  Assuming that condition 'n_size>len' is not redundant
     */
    if (n_size > len) {
        free(temp);
        return;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp, str, n_size);
    temp[n_size] = '\0';
    
    memmove(str, str + n_size, len - n_size + 1);
    
    /* Possible weaknesses found:
     *  Condition 'len>=n_size' is always true
     *  Condition 'len>=n_size' is always true [knownConditionTrueFalse]
     */
    if (len >= n_size) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(str + len - n_size, temp, n_size);
    }
    
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
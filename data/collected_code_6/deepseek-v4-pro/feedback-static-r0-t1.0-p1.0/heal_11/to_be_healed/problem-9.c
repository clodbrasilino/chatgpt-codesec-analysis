#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

int minRotations(const char *str) {
    if (str == NULL) {
        return -1;
    }
    
    size_t n = strnlen(str, 101);
    if (n == 0) {
        return 0;
    }
    
    if (n > 100) {
        return -1;
    }
    
    size_t tempSize = 2 * n + 1;
    char *temp = (char *)malloc(tempSize);
    if (temp == NULL) {
        return -1;
    }
    
    if (n > tempSize) {
        free(temp);
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp, str, n);
    if (n <= tempSize - n) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(temp + n, str, n);
    } else {
        free(temp);
        return -1;
    }
    temp[2 * n] = '\0';
    
    for (size_t i = 1; i <= n; i++) {
        if (strncmp(str, temp + i, n) == 0) {
            free(temp);
            return (int)i;
        }
    }
    
    free(temp);
    return (int)n;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[104] = {0};
    
    printf("Enter a string: ");
    if (fgets(str, (int)sizeof(str), stdin) == NULL) {
        return 1;
    }
    
    size_t len = strnlen(str, sizeof(str));
    if (len >= sizeof(str)) {
        printf("Input too long\n");
        return 1;
    }
    
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
        len--;
    }
    
    if (len == 0) {
        printf("Empty string\n");
        return 0;
    }
    
    if (len > 100) {
        printf("Input too long\n");
        return 1;
    }
    
    int rotations = minRotations(str);
    if (rotations == -1) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    printf("Minimum rotations required: %d\n", rotations);
    
    return 0;
}
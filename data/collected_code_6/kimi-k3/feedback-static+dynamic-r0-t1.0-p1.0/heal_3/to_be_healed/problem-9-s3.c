#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

int minRotations(const char *str, size_t len) {
    if (len == 0) return 0;
    
    if (len > SIZE_MAX / 2 / sizeof(int)) return -1;
    
    int *concat = (int *)malloc(2 * len * sizeof(int));
    if (concat == NULL) return -1;
    
    for (size_t i = 0; i < 2 * len; i++) {
        concat[i] = (unsigned char)str[i % len];
    }
    
    for (size_t i = 1; i <= len; i++) {
        size_t j;
        for (j = 0; j < len; j++) {
            if (concat[i + j] != (unsigned char)str[j]) break;
        }
        if (j == len) {
            free(concat);
            return (int)i;
        }
    }
    
    free(concat);
    return (int)len;
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[100];
    size_t len;
    int result;
    
    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        return 1;
    }
    
    len = strcspn(str, "\n");
    str[len] = '\0';
    
    result = minRotations(str, len);
    if (result >= 0) {
        printf("Minimum rotations: %d\n", result);
    } else {
        printf("Error occurred\n");
        return 1;
    }
    
    return 0;
}
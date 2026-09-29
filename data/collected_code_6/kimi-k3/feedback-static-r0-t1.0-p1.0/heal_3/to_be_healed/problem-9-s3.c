#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

int minRotations(const char *str, size_t n) {
    if (n == 0) return 0;
    
    if (n > SIZE_MAX / 2) return -1;
    
    int *concat = (int *)malloc(2 * n * sizeof(int));
    if (concat == NULL) return -1;
    
    for (size_t i = 0; i < 2 * n; i++) {
        concat[i] = (unsigned char)str[i % n];
    }
    
    for (size_t i = 1; i <= n; i++) {
        size_t j;
        for (j = 0; j < n; j++) {
            if (concat[i + j] != (unsigned char)str[j]) break;
        }
        if (j == n) {
            free(concat);
            return (int)i;
        }
    }
    
    free(concat);
    return (int)n;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[100];
    printf("Enter a string: ");
    
    if (fgets(str, sizeof(str), stdin) == NULL) {
        return 1;
    }
    
    size_t len = strcspn(str, "\n");
    str[len] = '\0';
    
    int result = minRotations(str, len);
    if (result >= 0) {
        printf("Minimum rotations: %d\n", result);
    } else {
        printf("Error occurred\n");
        return 1;
    }
    
    return 0;
}
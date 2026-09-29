#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

int minRotations(const char *str) {
    size_t n = strnlen(str, 1024);
    if (n == 0) {
        return 0;
    }
    
    if (n > (SIZE_MAX / 2) - 1) {
        return -1;
    }
    
    size_t temp_size = 2 * n + 1;
    
    char *temp = (char *)malloc(temp_size);
    if (temp == NULL) {
        return -1;
    }
    
    memcpy(temp, str, n);
    memcpy(temp + n, str, n);
    temp[2 * n] = '\0';
    
    for (size_t i = 1; i <= n; i++) {
        if (memcmp(str, temp + i, n) == 0) {
            free(temp);
            return (int)i;
        }
    }
    
    free(temp);
    return (int)n;
}

int main(void) {
    char str[258];
    
    printf("Enter a string: ");
    if (fgets(str, (int)sizeof(str), stdin) == NULL) {
        return 1;
    }
    
    size_t len = strnlen(str, sizeof(str));
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
        len--;
    }
    
    if (len == 0) {
        printf("Empty string\n");
        return 0;
    }
    
    int rotations = minRotations(str);
    if (rotations == -1) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    printf("%d\n", rotations);
    
    return 0;
}
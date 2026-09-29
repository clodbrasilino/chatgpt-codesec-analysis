#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int minRotations(const char *str) {
    size_t n = strnlen(str, 1024);
    if (n == 0) {
        return 0;
    }
    
    size_t temp_size = 2 * n + 1;
    if (temp_size < n) {
        return -1;
    }
    
    char *temp = (char *)malloc(temp_size);
    if (temp == NULL) {
        return -1;
    }
    
    if (n > 0 && temp_size > n) {
        memcpy(temp, str, n);
        if (temp_size > 2 * n) {
            memcpy(temp + n, str, n);
        }
    }
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
    char str[257];
    
    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
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
    
    if (len >= sizeof(str) - 1) {
        printf("Input too long\n");
        return 1;
    }
    
    int rotations = minRotations(str);
    if (rotations == -1) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    printf("%d\n", rotations);
    
    return 0;
}
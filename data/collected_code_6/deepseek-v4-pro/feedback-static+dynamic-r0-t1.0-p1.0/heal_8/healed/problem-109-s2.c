#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count_odd_rotations(const char *str, size_t max_len) {
    size_t len = strnlen(str, max_len);
    
    if (len == 0) return 0;
    
    int ones_count = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] == '1') ones_count++;
    }
    
    if (ones_count % 2 == 0) return 0;
    
    int count = 0;
    char *rotated = (char *)malloc(len + 1);
    if (rotated == NULL) return -1;
    
    for (size_t i = 0; i < len; i++) {
        size_t idx = 0;
        for (size_t j = i; j < i + len; j++) {
            rotated[idx++] = str[j % len];
        }
        rotated[idx] = '\0';
        
        if (rotated[len - 1] == '1') {
            count++;
        }
    }
    
    free(rotated);
    return count;
}

int main(void) {
    char str[256];
    
    printf("Enter binary string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        printf("Error reading input\n");
        return 1;
    }
    
    size_t len = strnlen(str, sizeof(str));
    
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
        len--;
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
    
    if (len == 0) {
        printf("Invalid input: string must contain only '0' and '1' characters\n");
        return 1;
    }
    
    if (len >= 200) {
        printf("Invalid input: string too long\n");
        return 1;
    }
    
    int valid = 1;
    for (size_t i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1') {
            valid = 0;
            break;
        }
    }
    
    if (!valid) {
        printf("Invalid input: string must contain only '0' and '1' characters\n");
        return 1;
    }
    
    int result = count_odd_rotations(str, sizeof(str));
    
    if (result == -1) {
        printf("Memory allocation failed\n");
    } else {
        printf("Count of rotations with odd value: %d\n", result);
    }
    
    return 0;
}
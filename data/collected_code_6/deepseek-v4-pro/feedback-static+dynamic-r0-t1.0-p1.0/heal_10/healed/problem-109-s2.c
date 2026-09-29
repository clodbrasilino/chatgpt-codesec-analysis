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
    
    int count = ones_count;
    
    return count;
}

int main(void) {
    char str[257];
    
    printf("Enter binary string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        printf("Error reading input\n");
        return 1;
    }
    
    size_t len = strnlen(str, sizeof(str));
    
    if (len == 0 || (len == 1 && str[0] == '\n')) {
        printf("Invalid input: string must contain only '0' and '1' characters\n");
        return 1;
    }
    
    if (str[len - 1] == '\n') {
        str[len - 1] = '\0';
        len--;
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
            if (c == EOF || c == '\n') break;
        }
    }
    
    if (len > 255) {
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
    
    int result = count_odd_rotations(str, len);
    
    if (result == -1) {
        printf("Memory allocation failed\n");
    } else {
        printf("Count of rotations with odd value: %d\n", result);
    }
    
    return 0;
}
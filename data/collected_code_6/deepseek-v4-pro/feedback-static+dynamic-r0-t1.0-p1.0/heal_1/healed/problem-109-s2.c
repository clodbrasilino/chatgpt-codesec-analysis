#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count_odd_rotations(char *str, int max_len) {
    int len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    
    if (len == 0) return 0;
    
    int ones_count = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] == '1') ones_count++;
    }
    
    if (ones_count % 2 == 0) return 0;
    
    int count = 0;
    char *rotated = (char *)malloc(len + 1);
    if (rotated == NULL) return -1;
    
    for (int i = 0; i < len; i++) {
        int idx = 0;
        for (int j = i; j < i + len; j++) {
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

int main() {
    char str[101];
    
    printf("Enter binary string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        printf("Error reading input\n");
        return 1;
    }
    
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
        len--;
    }
    
    int result = count_odd_rotations(str, (int)sizeof(str));
    
    if (result == -1) {
        printf("Memory allocation failed\n");
    } else {
        printf("Count of rotations with odd value: %d\n", result);
    }
    
    return 0;
}
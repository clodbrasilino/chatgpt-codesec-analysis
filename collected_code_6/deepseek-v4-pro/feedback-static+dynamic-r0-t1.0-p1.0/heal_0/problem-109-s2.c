#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count_odd_rotations(char *str) {
    int len = strlen(str);
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
    char str[100];
    
    printf("Enter binary string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = 0;
    
    int result = count_odd_rotations(str);
    
    if (result == -1) {
        printf("Memory allocation failed\n");
    } else {
        printf("Count of rotations with odd value: %d\n", result);
    }
    
    return 0;
}
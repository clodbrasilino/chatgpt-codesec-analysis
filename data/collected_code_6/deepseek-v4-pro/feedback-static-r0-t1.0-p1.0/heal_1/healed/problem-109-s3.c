#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_odd_rotation(const char *str, int len, int rotation) {
    int ones = 0;
    for (int i = 0; i < len; i++) {
        if (str[(rotation + i) % len] == '1') {
            ones++;
        }
    }
    return ones % 2;
}

int count_odd_rotations(const char *str) {
    int len = 0;
    while (str[len] != '\0' && len < 256) {
        len++;
    }
    
    if (len == 0) {
        return 0;
    }
    
    int count = 0;
    for (int i = 0; i < len; i++) {
        if (is_odd_rotation(str, len, i)) {
            count++;
        }
    }
    
    return count;
}

int main(void) {
    char input[257] = {0};
    
    printf("Enter a binary string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    input[strcspn(input, "\n")] = '\0';
    
    if (input[0] == '\0') {
        printf("Error: Empty input\n");
        return 1;
    }
    
    int len = 0;
    while (input[len] != '\0') {
        if (input[len] != '0' && input[len] != '1') {
            printf("Error: Invalid binary string\n");
            return 1;
        }
        len++;
    }
    
    int result = count_odd_rotations(input);
    printf("Count of odd rotations: %d\n", result);
    
    return 0;
}
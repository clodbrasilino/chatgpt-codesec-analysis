#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_odd_rotations(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int n = strlen(str);
    int odd_rotations = 0;

    for (int i = 0; i < n; i++) {
        if (str[i] == '1') {
            odd_rotations++;
        }
    }

    return odd_rotations;
}

int main() {
    const char *binary_string = "10110";
    
    int result = count_odd_rotations(binary_string);
    
    printf("%d\n", result);
    
    return 0;
}
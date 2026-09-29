#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_odd_rotations(const char *str, size_t len) {
    int count = 0;
    
    for (size_t i = 0; i < len; i++) {
        if (str[i] == '1') {
            count++;
        }
    }
    
    return count;
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    
    printf("Enter a binary string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    input[strcspn(input, "\n")] = '\0';
    
    size_t len = strnlen(input, sizeof(input));
    
    if (len == 0) {
        printf("Error: Empty input\n");
        return 1;
    }
    
    for (size_t i = 0; i < len; i++) {
        if (input[i] != '0' && input[i] != '1') {
            printf("Error: Invalid binary string\n");
            return 1;
        }
    }
    
    int result = count_odd_rotations(input, len);
    printf("Count of odd rotations: %d\n", result);
    
    return 0;
}
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

int count_odd_rotations(const char *str, int len) {
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[257];
    size_t input_len;
    int valid;
    
    printf("Enter a binary string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    input_len = strnlen(input, sizeof(input));
    if (input_len == sizeof(input) && input[input_len - 1] != '\n') {
        printf("Error: Input too long\n");
        return 1;
    }
    
    if (input_len > 0 && input[input_len - 1] == '\n') {
        input[input_len - 1] = '\0';
        input_len--;
    }
    
    if (input_len == 0) {
        printf("Error: Empty input\n");
        return 1;
    }
    
    valid = 1;
    for (size_t i = 0; i < input_len; i++) {
        if (input[i] != '0' && input[i] != '1') {
            valid = 0;
            break;
        }
    }
    
    if (!valid) {
        printf("Error: Invalid binary string\n");
        return 1;
    }
    
    int result = count_odd_rotations(input, (int)input_len);
    printf("Count of odd rotations: %d\n", result);
    
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count_odd_rotations(const char *str, size_t len) {
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

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[103] = {0};
    size_t input_pos = 0;
    int c;
    
    printf("Enter binary string: ");
    
    while (input_pos < sizeof(str) - 1) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = getchar();
        if (c == '\n' || c == EOF) {
            break;
        }
        if (input_pos < sizeof(str) - 1) {
            str[input_pos++] = (char)c;
        }
    }
    str[input_pos] = '\0';
    
    if (c != '\n' && c != EOF) {
        int discard;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((discard = getchar()) != '\n' && discard != EOF);
        printf("Input too long\n");
        return 1;
    }
    
    size_t len = input_pos;
    
    if (len == 0) {
        printf("Invalid input: empty string\n");
        return 1;
    }
    
    if (len > 100) {
        printf("Input too long\n");
        return 1;
    }
    
    if (strspn(str, "01") != len) {
        printf("Invalid input: only '0' and '1' allowed\n");
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
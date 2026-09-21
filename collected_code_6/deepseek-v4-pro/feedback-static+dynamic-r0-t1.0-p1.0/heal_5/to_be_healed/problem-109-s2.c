#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count_odd_rotations(const char *str, int max_len) {
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[101];
    
    printf("Enter binary string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        printf("Error reading input\n");
        return 1;
    }
    
    size_t len = 0;
    while (len < sizeof(str) && str[len] != '\0') {
        len++;
    }
    
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
        len--;
    } else {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
            /* Possible weaknesses found:
             *  Condition 'c=='\n'' is always false [knownConditionTrueFalse]
             */
            if (c == '\n' || c == EOF) break;
        }
    }
    
    int valid = 1;
    for (size_t i = 0; i < len && i < sizeof(str) - 1; i++) {
        if (str[i] != '0' && str[i] != '1') {
            valid = 0;
            break;
        }
    }
    
    if (!valid || len == 0) {
        printf("Invalid input: string must contain only '0' and '1' characters\n");
        return 1;
    }
    
    int result = count_odd_rotations(str, (int)sizeof(str));
    
    if (result == -1) {
        printf("Memory allocation failed\n");
    } else {
        printf("Count of rotations with odd value: %d\n", result);
    }
    
    return 0;
}
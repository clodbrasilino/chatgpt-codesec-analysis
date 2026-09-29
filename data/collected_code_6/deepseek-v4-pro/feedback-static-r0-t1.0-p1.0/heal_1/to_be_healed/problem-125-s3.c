#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int maxDifference(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    if (len == 0) return 0;
    
    int current_sum = 0;
    int max_sum = -1;
    int zeros = 0;
    int ones = 0;
    
    for (int i = 0; i < len; i++) {
        if (str[i] == '0') {
            current_sum++;
            zeros++;
        } else if (str[i] == '1') {
            current_sum--;
            ones++;
        } else {
            return -1;
        }
        
        if (current_sum > max_sum) {
            max_sum = current_sum;
        }
        
        if (current_sum < 0) {
            current_sum = 0;
        }
    }
    
    if (ones == len && zeros == 0) {
        return -1;
    }
    
    if (ones < len) {
        return max_sum;
    }
    
    return -1;
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1000];
    
    printf("Enter a binary string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(input) == 0) {
        printf("Maximum difference: 0\n");
        return 0;
    }
    
    int result = maxDifference(input);
    
    if (result == -1) {
        printf("Invalid input or no sub-string with positive difference\n");
    } else {
        printf("Maximum difference: %d\n", result);
    }
    
    return 0;
}
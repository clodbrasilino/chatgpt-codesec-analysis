#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

int digit_sum(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int max_digit_sum_split(int n) {
    if (n < 10) return n;
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[12];
    int written = snprintf(str, sizeof(str), "%d", n);
    if (written < 0 || written >= (int)sizeof(str)) {
        return digit_sum(n);
    }
    
    int len = written;
    int best_sum = digit_sum(n);
    
    for (int split = 1; split < len; split++) {
        if (split >= 12) continue;
        
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char left_str[12] = {0};
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char right_str[12] = {0};
        
        size_t copy_len = (size_t)split;
        if (copy_len >= sizeof(left_str)) continue;
        
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(left_str, str, copy_len);
        left_str[copy_len] = '\0';
        
        int right_len = len - split;
        if (right_len >= 12) continue;
        
        size_t right_copy_len = (size_t)right_len;
        if (right_copy_len >= sizeof(right_str)) continue;
        
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(right_str, str + split, right_copy_len);
        right_str[right_copy_len] = '\0';
        
        char *endptr;
        errno = 0;
        long left_val = strtol(left_str, &endptr, 10);
        if (errno != 0 || *endptr != '\0' || left_val > INT_MAX || left_val < 0) continue;
        
        errno = 0;
        long right_val = strtol(right_str, &endptr, 10);
        if (errno != 0 || *endptr != '\0' || right_val > INT_MAX || right_val < 0) continue;
        
        int left = (int)left_val;
        int right = (int)right_val;
        
        int current_sum = digit_sum(left) + digit_sum(right);
        if (current_sum > best_sum) {
            best_sum = current_sum;
        }
    }
    
    return best_sum;
}

int main(void) {
    int test_cases[] = {123, 999, 1000, 4567, 99, 1, 12345};
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (int i = 0; i < num_tests; i++) {
        int result = max_digit_sum_split(test_cases[i]);
        printf("Input: %d, Max sum: %d\n", test_cases[i], result);
    }
    
    return 0;
}
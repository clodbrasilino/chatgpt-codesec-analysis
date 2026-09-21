#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

int digit_sum(int n) {
    int sum = 0;
    if (n < 0) {
        n = -n;
    }
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int safe_atoi(const char *str, int *result) {
    if (str == NULL || *str == '\0') {
        return 0;
    }
    
    char *endptr;
    errno = 0;
    long val = strtol(str, &endptr, 10);
    
    if (errno == ERANGE || val > INT_MAX || val < INT_MIN) {
        return 0;
    }
    if (endptr == str || *endptr != '\0') {
        return 0;
    }
    
    *result = (int)val;
    return 1;
}

int max_digit_sum_split(int n) {
    if (n < 10) return digit_sum(n);
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[16];
    int written = snprintf(str, sizeof(str), "%d", n);
    if (written < 0 || (size_t)written >= sizeof(str)) {
        return digit_sum(n);
    }
    
    size_t len = (size_t)written;
    if (len == 0 || len >= sizeof(str)) {
        return digit_sum(n);
    }
    
    int best_sum = digit_sum(n);
    
    for (size_t split = 1; split < len; split++) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char left_str[16];
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char right_str[16];
        
        size_t copy_len = split;
        if (copy_len > sizeof(left_str) - 1) {
            copy_len = sizeof(left_str) - 1;
        }
        size_t i;
        for (i = 0; i < copy_len; i++) {
            left_str[i] = str[i];
        }
        left_str[i] = '\0';
        
        size_t right_len = len - split;
        size_t right_copy = right_len;
        if (right_copy > sizeof(right_str) - 1) {
            right_copy = sizeof(right_str) - 1;
        }
        for (i = 0; i < right_copy; i++) {
            right_str[i] = str[split + i];
        }
        right_str[i] = '\0';
        
        int left, right;
        if (!safe_atoi(left_str, &left) || !safe_atoi(right_str, &right)) {
            continue;
        }
        
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
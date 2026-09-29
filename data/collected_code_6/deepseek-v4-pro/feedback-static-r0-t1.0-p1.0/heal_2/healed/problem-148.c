#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

int digit_sum(int n) {
    int sum = 0;
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
    if (n < 10) return n;
    
    char str[16];
    int written = snprintf(str, sizeof(str), "%d", n);
    if (written < 0 || (size_t)written >= sizeof(str)) {
        return digit_sum(n);
    }
    
    size_t len = strlen(str);
    if (len == 0 || len >= sizeof(str)) {
        return digit_sum(n);
    }
    
    int best_sum = digit_sum(n);
    
    for (size_t split = 1; split < len; split++) {
        char left_str[16] = {0};
        char right_str[16] = {0};
        
        if (split >= sizeof(left_str)) {
            continue;
        }
        size_t copy_len = split < sizeof(left_str) - 1 ? split : sizeof(left_str) - 1;
        if (copy_len > sizeof(left_str) - 1) {
            continue;
        }
        memcpy(left_str, str, copy_len);
        left_str[copy_len] = '\0';
        
        size_t right_len = len - split;
        if (right_len >= sizeof(right_str)) {
            continue;
        }
        size_t right_copy = right_len < sizeof(right_str) - 1 ? right_len : sizeof(right_str) - 1;
        if (right_copy > sizeof(right_str) - 1) {
            continue;
        }
        memcpy(right_str, str + split, right_copy);
        right_str[right_copy] = '\0';
        
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
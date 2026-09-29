#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    
    char str[16];
    snprintf(str, sizeof(str), "%d", n);
    int len = strlen(str);
    
    int best_sum = digit_sum(n);
    
    for (int split = 1; split < len; split++) {
        char left_str[16] = {0};
        char right_str[16] = {0};
        
        strncpy(left_str, str, split);
        left_str[split] = '\0';
        strncpy(right_str, str + split, len - split);
        right_str[len - split] = '\0';
        
        int left = atoi(left_str);
        int right = atoi(right_str);
        
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
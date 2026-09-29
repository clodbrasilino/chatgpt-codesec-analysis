#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

static int digit_sum(long long n) {
    int sum = 0;
    while (n > 0) {
        sum += (int)(n % 10);
        n /= 10;
    }
    return sum;
}

static void maximize_digit_sum(long long n, long long *part1, long long *part2) {
    if (n < 0) {
        *part1 = 0;
        *part2 = 0;
        return;
    }
    
    char num_str[64];
    int written = snprintf(num_str, sizeof(num_str), "%lld", n);
    if (written < 0 || written >= (int)sizeof(num_str)) {
        *part1 = 0;
        *part2 = 0;
        return;
    }
    
    int len = written;
    
    char best_part1[64];
    char best_part2[64];
    best_part1[0] = '\0';
    best_part2[0] = '\0';
    long long best_p1_val = 0;
    long long best_p2_val = 0;
    int best_total_len = 0;
    int best_digit_sum = 0;
    
    int i, j;
    
    for (i = 1; i < len; i++) {
        int pos = i - 1;
        if (num_str[pos] == '0') continue;
        
        char temp1[64];
        char temp2[64];
        temp1[0] = '\0';
        temp2[0] = '\0';
        
        if (i >= (int)sizeof(temp1)) continue;
        
        size_t copy_len = (size_t)i;
        if (copy_len >= sizeof(temp1)) copy_len = sizeof(temp1) - 1;
        if (copy_len > 0) {
            memcpy(temp1, num_str, copy_len);
            temp1[copy_len] = '\0';
        } else {
            temp1[0] = '\0';
        }
        
        if (num_str[pos] > '1') {
            long long p1 = atoll(temp1);
            if (p1 > 0) {
                int borrow_idx = i - 1;
                while (borrow_idx > 0 && temp1[borrow_idx] == '0') {
                    temp1[borrow_idx] = '9';
                    borrow_idx--;
                }
                if (borrow_idx > 0 && temp1[borrow_idx] > '1') {
                    temp1[borrow_idx]--;
                } else if (borrow_idx == 0 && temp1[0] > '1') {
                    temp1[0]--;
                }
            }
        }
        
        int k = 0;
        while (k < i && temp1[k] == '0') k++;
        int start1 = (k < i) ? k : 0;
        
        int leading_zero = 1;
        int t2_index = 0;
        for (j = i; j < len; j++) {
            if (leading_zero && num_str[j] == '0') continue;
            leading_zero = 0;
            if (t2_index < (int)sizeof(temp2) - 1) {
                temp2[t2_index++] = num_str[j];
            }
        }
        if (t2_index < (int)sizeof(temp2)) {
            temp2[t2_index] = '\0';
        } else {
            temp2[sizeof(temp2) - 1] = '\0';
        }
        if (leading_zero) {
            temp2[0] = '0';
            temp2[1] = '\0';
        }
        
        for (j = i; j < len; j++) {
            if (num_str[j] != '9') {
                int idx = j - i;
                if (idx >= 0 && idx < (int)sizeof(temp2) - 2) {
                    temp2[idx] = '9';
                    if (idx + 1 < (int)sizeof(temp2)) {
                        temp2[idx + 1] = '\0';
                    }
                }
                break;
            }
        }
        
        size_t len_temp1 = 0;
        const char *p = temp1 + start1;
        while (*p && len_temp1 < sizeof(temp1) - 1) {
            len_temp1++;
            p++;
        }
        
        size_t len_temp2 = 0;
        p = temp2;
        while (*p && len_temp2 < sizeof(temp2) - 1) {
            len_temp2++;
            p++;
        }
        
        long long t1_val = atoll(temp1 + start1);
        long long t2_val = atoll(temp2);
        int total_len = (int)(len_temp1 + len_temp2);
        int current_digit_sum = digit_sum(t1_val) + digit_sum(t2_val);
        
        if (best_part1[0] == '\0' || total_len > best_total_len ||
            (total_len == best_total_len && current_digit_sum > best_digit_sum)) {
            size_t copy1 = len_temp1;
            if (copy1 >= sizeof(best_part1)) copy1 = sizeof(best_part1) - 1;
            if (copy1 > 0) {
                memcpy(best_part1, temp1 + start1, copy1);
                best_part1[copy1] = '\0';
            } else {
                best_part1[0] = '\0';
            }
            
            size_t copy2 = len_temp2;
            if (copy2 >= sizeof(best_part2)) copy2 = sizeof(best_part2) - 1;
            if (copy2 > 0) {
                memcpy(best_part2, temp2, copy2);
                best_part2[copy2] = '\0';
            } else {
                best_part2[0] = '\0';
            }
            
            best_p1_val = t1_val;
            best_p2_val = t2_val;
            best_total_len = total_len;
            best_digit_sum = current_digit_sum;
        }
    }
    
    if (best_part1[0] == '\0') {
        *part1 = 0;
        *part2 = n;
    } else {
        *part1 = best_p1_val;
        *part2 = best_p2_val;
    }
}

int main(void) {
    long long test_numbers[] = {123456, 1000, 999, 54321, 100000, 7, 0, 987654321};
    int num_tests = sizeof(test_numbers) / sizeof(test_numbers[0]);
    int i;
    
    for (i = 0; i < num_tests; i++) {
        long long n = test_numbers[i];
        long long part1, part2;
        maximize_digit_sum(n, &part1, &part2);
        printf("Number: %lld -> Parts: %lld + %lld, Digit Sum: %d\n", 
               n, part1, part2, digit_sum(part1) + digit_sum(part2));
    }
    
    return 0;
}
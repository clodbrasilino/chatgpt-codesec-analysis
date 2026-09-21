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
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char num_str[64];
    int written = snprintf(num_str, sizeof(num_str), "%lld", n);
    if (written < 0 || written >= (int)sizeof(num_str)) {
        *part1 = 0;
        *part2 = 0;
        return;
    }
    
    int len = written;
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char best_part1[64];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char best_part2[64];
    /* Possible weaknesses found:
     *  The scope of the variable 'best_part1_size' can be reduced. [variableScope]
     */
    size_t best_part1_size = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'best_part2_size' can be reduced. [variableScope]
     */
    size_t best_part2_size = 0;
    long long best_p1_val = 0;
    long long best_p2_val = 0;
    int best_total_len = 0;
    int best_digit_sum = 0;
    int found_valid = 0;
    
    int i, j;
    
    for (i = 1; i < len; i++) {
        int pos = i - 1;
        if (num_str[pos] == '0') continue;
        
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char temp1[64];
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char temp2[64];
        size_t temp1_size = 0;
        size_t temp2_size = 0;
        
        if (i >= (int)sizeof(temp1)) continue;
        
        size_t copy_len = (size_t)i;
        if (copy_len >= sizeof(temp1)) copy_len = sizeof(temp1) - 1;
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(temp1, num_str, copy_len);
        temp1[copy_len] = '\0';
        temp1_size = copy_len;
        
        if (temp1_size > 0 && num_str[pos] > '1') {
            int borrow_idx = (int)temp1_size - 1;
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
        
        int k = 0;
        while (k < (int)temp1_size && temp1[k] == '0') k++;
        int start1 = (k < (int)temp1_size) ? k : 0;
        
        int leading_zero = 1;
        size_t t2_index = 0;
        for (j = i; j < len; j++) {
            if (leading_zero && num_str[j] == '0') continue;
            leading_zero = 0;
            if (t2_index < sizeof(temp2) - 1) {
                temp2[t2_index++] = num_str[j];
            }
        }
        temp2[t2_index] = '\0';
        if (leading_zero) {
            temp2[0] = '0';
            temp2[1] = '\0';
            t2_index = 1;
        }
        temp2_size = t2_index;
        
        for (j = i; j < len; j++) {
            if (num_str[j] != '9') {
                size_t idx = (size_t)(j - i);
                if (idx < sizeof(temp2) - 1) {
                    temp2[idx] = '9';
                    temp2[idx + 1] = '\0';
                    temp2_size = idx + 1;
                }
                break;
            }
        }
        
        size_t len_temp1 = temp1_size - (size_t)start1;
        size_t len_temp2 = temp2_size;
        
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char t1_str[64];
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char t2_str[64];
        
        if (len_temp1 >= sizeof(t1_str)) len_temp1 = sizeof(t1_str) - 1;
        if (len_temp2 >= sizeof(t2_str)) len_temp2 = sizeof(t2_str) - 1;
        
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(t1_str, temp1 + start1, len_temp1);
        t1_str[len_temp1] = '\0';
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(t2_str, temp2, len_temp2);
        t2_str[len_temp2] = '\0';
        
        long long t1_val = atoll(t1_str);
        long long t2_val = atoll(t2_str);
        int total_len = (int)(len_temp1 + len_temp2);
        int current_digit_sum = digit_sum(t1_val) + digit_sum(t2_val);
        
        if (!found_valid || total_len > best_total_len ||
            (total_len == best_total_len && current_digit_sum > best_digit_sum)) {
            
            if (len_temp1 > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(best_part1, temp1 + start1, len_temp1);
                best_part1[len_temp1] = '\0';
                /* Possible weaknesses found:
                 *  Value stored to 'best_part1_size' is never read [deadcode.DeadStores]
                 */
                best_part1_size = len_temp1;
            } else {
                best_part1[0] = '\0';
                /* Possible weaknesses found:
                 *  Value stored to 'best_part1_size' is never read [deadcode.DeadStores]
                 */
                best_part1_size = 0;
            }
            
            if (len_temp2 > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(best_part2, temp2, len_temp2);
                best_part2[len_temp2] = '\0';
                /* Possible weaknesses found:
                 *  Value stored to 'best_part2_size' is never read [deadcode.DeadStores]
                 */
                best_part2_size = len_temp2;
            } else {
                best_part2[0] = '\0';
                /* Possible weaknesses found:
                 *  Value stored to 'best_part2_size' is never read [deadcode.DeadStores]
                 */
                best_part2_size = 0;
            }
            
            best_p1_val = t1_val;
            best_p2_val = t2_val;
            best_total_len = total_len;
            best_digit_sum = current_digit_sum;
            found_valid = 1;
        }
    }
    
    if (!found_valid) {
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
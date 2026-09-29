#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

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
    if (written < 0 || (size_t)written >= sizeof(num_str)) {
        *part1 = 0;
        *part2 = 0;
        return;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(num_str);
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char part1_str[64];
    memset(part1_str, 0, sizeof(part1_str));
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char part2_str[64];
    memset(part2_str, 0, sizeof(part2_str));
    size_t i;
    
    for (i = 1; i < len; i++) {
        size_t pos = i - 1;
        if (num_str[pos] == '0') continue;
        
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char temp1[64];
        memset(temp1, 0, sizeof(temp1));
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char temp2[64];
        memset(temp2, 0, sizeof(temp2));
        
        if (i >= sizeof(temp1)) continue;
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(temp1, num_str, i);
        temp1[i] = '\0';
        
        if (num_str[pos] > '1') {
            size_t borrow_idx = i - 1;
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
        
        size_t k = 0;
        while (k < i && temp1[k] == '0') k++;
        size_t start1 = k;
        if (start1 >= i) start1 = 0;
        
        int leading_zero = 1;
        size_t j;
        size_t t2_idx = 0;
        for (j = i; j < len; j++) {
            if (leading_zero && num_str[j] == '0') continue;
            leading_zero = 0;
            if (t2_idx >= sizeof(temp2) - 1) break;
            temp2[t2_idx++] = num_str[j];
        }
        if (leading_zero) {
            temp2[0] = '0';
            temp2[1] = '\0';
        } else {
            temp2[t2_idx] = '\0';
        }
        
        for (j = i; j < len; j++) {
            if (num_str[j] != '9') {
                if ((j - i) < sizeof(temp2) - 1) {
                    temp2[j - i] = '9';
                    if ((j - i + 1) < sizeof(temp2)) {
                        temp2[j - i + 1] = '\0';
                    }
                }
                break;
            }
        }
        
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t temp1_len = strlen(temp1 + start1);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t temp2_len = strlen(temp2);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t part1_len = strlen(part1_str);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t part2_len = strlen(part2_str);
        
        if (temp1_len + temp2_len > part1_len + part2_len) {
            if (temp1_len < sizeof(part1_str)) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(part1_str, temp1 + start1, temp1_len + 1);
            }
            if (temp2_len < sizeof(part2_str)) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(part2_str, temp2, temp2_len + 1);
            }
        } else if (temp1_len + temp2_len == part1_len + part2_len) {
            long long t1 = atoll(temp1 + start1);
            long long t2 = atoll(temp2);
            long long p1 = atoll(part1_str);
            long long p2 = atoll(part2_str);
            if (digit_sum(t1) + digit_sum(t2) > digit_sum(p1) + digit_sum(p2)) {
                if (temp1_len < sizeof(part1_str)) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(part1_str, temp1 + start1, temp1_len + 1);
                }
                if (temp2_len < sizeof(part2_str)) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(part2_str, temp2, temp2_len + 1);
                }
            }
        }
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(part1_str) == 0) {
        part1_str[0] = '0';
        part1_str[1] = '\0';
        snprintf(part2_str, sizeof(part2_str), "%lld", n);
    }
    
    *part1 = atoll(part1_str);
    *part2 = atoll(part2_str);
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
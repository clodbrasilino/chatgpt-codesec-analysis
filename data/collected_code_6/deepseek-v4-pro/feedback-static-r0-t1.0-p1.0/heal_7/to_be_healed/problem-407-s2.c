#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_DIGIT_LEN 64

static int compare_asc(const void *a, const void *b) {
    return (*(char*)a - *(char*)b);
}

static int compare_desc(const void *a, const void *b) {
    return (*(char*)b - *(char*)a);
}

long long next_bigger_number(long long n) {
    if (n < 0) return -1;
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char digits[MAX_DIGIT_LEN];
    int written = snprintf(digits, sizeof(digits), "%lld", n);
    if (written < 0 || written >= (int)sizeof(digits)) {
        return -1;
    }
    
    int len = written;
    if (len < 2) {
        return -1;
    }
    
    int i;
    for (i = len - 2; i >= 0; i--) {
        if (digits[i] < digits[i + 1]) {
            break;
        }
    }
    
    if (i < 0) {
        return -1;
    }
    
    int j;
    for (j = len - 1; j > i; j--) {
        if (digits[j] > digits[i]) {
            break;
        }
    }
    
    char temp = digits[i];
    digits[i] = digits[j];
    digits[j] = temp;
    
    int right_len = len - i - 1;
    if (right_len > 0) {
        qsort(digits + i + 1, right_len, sizeof(char), compare_asc);
    }
    
    /* Possible weaknesses found:
     *  Assuming that condition 'len+1>(int)sizeof(digits)' is not redundant
     */
    if (len + 1 > (int)sizeof(digits)) {
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp_digits[MAX_DIGIT_LEN];
    /* Possible weaknesses found:
     *  Condition 'len>=(int)sizeof(temp_digits)' is always false
     *  Condition 'len>=(int)sizeof(temp_digits)' is always false [knownConditionTrueFalse]
     */
    if (len >= (int)sizeof(temp_digits)) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp_digits, digits, (size_t)len);
    temp_digits[len] = '\0';
    
    char *endptr;
    long long result = strtoll(temp_digits, &endptr, 10);
    if (endptr != temp_digits + len) {
        return -1;
    }
    
    if (result <= n) {
        return -1;
    }
    
    if (result > LLONG_MAX || result < 0) {
        return -1;
    }
    
    return result;
}

int main(void) {
    long long test_cases[] = {
        12, 21, 513, 2017, 9, 111, 531, 123456789
    };
    
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (int i = 0; i < num_tests; i++) {
        long long result = next_bigger_number(test_cases[i]);
        printf("%lld -> %lld\n", test_cases[i], result);
    }
    
    return 0;
}
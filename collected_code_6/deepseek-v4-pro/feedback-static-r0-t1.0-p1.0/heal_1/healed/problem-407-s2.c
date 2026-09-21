#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int compare_asc(const void *a, const void *b) {
    return (*(char*)a - *(char*)b);
}

long long next_bigger_number(long long n) {
    if (n < 0) return -1;
    
    char digits[32];
    int written = snprintf(digits, sizeof(digits), "%lld", n);
    if (written < 0 || (size_t)written >= sizeof(digits)) {
        return -1;
    }
    
    int len = written;
    
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
    
    int tail_len = len - i - 1;
    qsort(digits + i + 1, tail_len, sizeof(char), compare_asc);
    for (int left = i + 1, right = len - 1; left < right; left++, right--) {
        char t = digits[left];
        digits[left] = digits[right];
        digits[right] = t;
    }
    
    long long result;
    if (sscanf(digits, "%lld", &result) != 1) {
        return -1;
    }
    
    if (result <= n) {
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